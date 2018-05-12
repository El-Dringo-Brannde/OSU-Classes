from models.CRUD import crud_model
from controllers.slip import slip_controller
from utility.utility import utility
import json


class boat_controller(crud_model):
    def __init__(self):
        self.set_db_collection("HW2", "Boats")
        self.slips = slip_controller()

    def add_boat(self, boatObj):
        boatObj['at_sea'] = True
        boatObj['docked_at'] = ""
        return self.create(boatObj)

    def query_boats(self, query):
        return json.loads(self.read(query))

    def get_boat(self, boat_id):
        search_obj = self.util.build_search_obj(boat_id)
        if not search_obj:
            return {'status': 503, 'Message': 'Bad Request.'}
        return json.loads(self.read(search_obj))

    def update_boat(self, boat_id, field, value):
        search_obj = self.util.build_search_obj(boat_id)
        if not search_obj:
            return False
        update_obj = {
            "$set": {
                field: value
            }
        }
        return self.update(search_obj, update_obj)

    def patch_boat(self, search_obj, patch_obj):
        update_obj = {
            "$set": patch_obj
        }
        return self.update(search_obj, update_obj)

    def delete_boat(self, boat_id):
        print(boat_id)
        search_obj = self.util.build_search_obj(boat_id)
        if not search_obj:
            return False
        return self.delete(search_obj)

    def find_spot(self, id):
        spots_open = self.slips.find_open_slip()
        if len(spots_open) == 0:
            return False
        else:
            return spots_open[0]

    def take_slip(self, id, slip_number):
        return self.slips.take_slip_number(id, slip_number)

    def clear_slip(self, slip_number):
        return self.slips.clear_slip_number(slip_number)
