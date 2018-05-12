from validators.slip import slip_validator
from bottle import get, post, patch, delete, put, request
import json

from routes.error import errors
from utility.utility import utility
from controllers.slip import slip_controller


class slip_routes:
    def __init__(self):
        self.slip_validator = slip_validator()
        self.controller = slip_controller()
        self.util = utility()
        self.error = errors()
        self.getRoutes()
        self.putRoutes()
        self.deleteRoutes()
        self.postRoutes()
        self.patchRoutes()

    def getRoutes(self):
        @get('/slips')
        def get_slips():
            query_obj = self.util.build_query_string(request.query)
            return self.controller.find_slip(query_obj)

        @get('/slips/<number>')
        def get_id(number):
            return self.controller.find_slip({'number': int(number)})

    def putRoutes(self):
        @put('/slip')
        def not_allowed():
            return self.error.cant_modify_slip()

        @put('/slip/<id>')
        def not_allowed(id):
            return self.error.cant_modify_slip()

    def deleteRoutes(self):
        @delete('/slip/<slip_id>')
        def delete_slip(slip_id):
            slip = self.controller.get_slip(slip_id)
            if not slip:
                return self.errors.invalid_slip_id()

            slip = slip[0]
            current_boat = slip['current_boat']

            if not slip['current_boat']:
                return self.controller.delete_slip(slip_id)
            else:
                slip = self.controller.delete_slip(slip_id)
                cleared_boat = self.controller.clear_boat(current_boat)
                return {
                    "boat": cleared_boat,
                    'slip': slip
                }

    def postRoutes(self):
        @post('/slip')
        def create_slip():
            return self.controller.add_slip()

    def patchRoutes(self):
        @patch('/slip')
        def not_allowed():
            return self.error.cant_modify_slip()

        @patch('/slip/<id>')
        def not_allowed(id):
            return self.error.cant_modify_slip()
