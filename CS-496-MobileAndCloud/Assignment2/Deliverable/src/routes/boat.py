from bottle import get, post, patch, delete, put, request
from controllers.boat import boat_controller
from validators.boat import boat_validator
from routes.error import errors
from utility.utility import utility
import json


class boat_routes:
    def __init__(self):
        self.controller = boat_controller()
        self.util = utility()
        self.getRoutes()
        self.putRoutes()
        self.deleteRoutes()
        self.postRoutes()
        self.patchRoutes()
        self.boat_validator = boat_validator()
        self.errors = errors()

    def getRoutes(self):
        @get('/boats')
        def boat():
            query_obj = self.util.build_query_string(request.query)
            return json.dumps(self.controller.query_boats(query_obj))

        @get('/boats/<boat_id>')
        def get_boat(boat_id):
            return json.dumps(self.controller.get_boat(boat_id))

        @get('/boats/at_sea')
        def at_sea():
            query_obj = {
                'at_sea': 'true'
            }
            return json.dumps(self.controller.query_boats(query_obj))

        @get('/boats/docked')
        def docked():
            query_obj = {'at_sea': 'false'}
            return json.dumps(self.controller.query_boats(query_obj))

    def putRoutes(self):
        @put('/boat')
        def not_allowed():
            return self.errors.cant_modify_boat()

        @put('/boat/<boat_id>')
        def not_allowed(boat_id):
            return self.errors.cant_modify_boat()

    def deleteRoutes(self):
        @delete('/boat/<boat_id>')
        def del_boat(boat_id):
            boat = self.controller.get_boat(boat_id)
            if not boat:
                return self.errors.invalid_boat_id()

            boat = boat[0]
            docked_at = boat['docked_at']
            if not boat['docked_at']:
                return self.controller.delete_boat(boat_id)
            else:
                boat = self.controller.delete_boat(boat_id)
                cleared_slip = self.controller.clear_slip(docked_at)
                return {
                    "boat": boat,
                    "slip": cleared_slip
                }

    def postRoutes(self):
        @post('/boat')
        def create_boat():
            if not request.body.read():
                return self.errors.bad_request()
            body = json.loads(request.body.read())

            if self.boat_validator.post(body) == False:
                return self.errors.bad_request()
            else:
                return self.controller.add_boat(body)

    def patchRoutes(self):
        @patch('/boat/<boat_id>/depart')
        def depart_boat(boat_id):  # handle already at sea issue
            boat = self.controller.get_boat(boat_id)
            if not boat:
                return self.errors.invalid_boat_id()

            boat = boat[0]
            if boat['at_sea'] == 'true':
                return self.errors.already_at_sea()

            slip_number = boat['docked_at']
            cleared_slip = self.controller.clear_slip(slip_number)
            boat_update = self.controller.update_boat(
                boat_id, "at_sea", "true")
            boat_update = self.controller.update_boat(boat_id, "docked_at", "")
            return {
                "slip": cleared_slip,
                "boat": boat_update
            }


########################################################################
        @patch('/boat/<boat_id>/arrival')
        def arrive_boat(boat_id):
            boat = self.controller.get_boat(boat_id)

            if not boat:
                return self.errors.invalid_boat_id()

            boat = boat[0]
            if boat['at_sea'] == 'false':
                return self.errors.already_docked()

            open_spot = self.controller.find_spot(boat_id)

            if not open_spot:
                return self.errors.no_spots()
            else:
                slip_number = open_spot['number']
                slip_update = self.controller.take_slip(boat_id, slip_number)
                boat_update = self.controller.update_boat(
                    boat_id, "at_sea", "false")
                boat_update = self.controller.update_boat(
                    boat_id, "docked_at", slip_number)
                return {
                    "slip": slip_update,
                    "boat": boat_update
                }

        @patch('/boat/<boat_id>')
        def patch_boat(boat_id):
            body = self.read_body(request.body.read())
            boat = self.controller.get_boat(boat_id)
            patch_validator = self.boat_validator.patch(body)
            if not patch_validator:
                return self.errors.bad_request()
            if not boat:
                return self.errors.invalid_boat_id()

            boat = boat[0]
            boat_id = self.util.build_search_obj(boat_id)
            boat = self.controller.patch_boat(boat_id, body)
            return boat

    def read_body(self, msg):
        return json.loads(msg)
