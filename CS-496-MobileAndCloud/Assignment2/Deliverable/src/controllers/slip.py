from models.CRUD import crud_model
from datetime import datetime
import json


class slip_controller(crud_model):
    def __init__(self):
        self.set_db_collection("HW2", "Slips")
        self.boats = None

    def find_open_slip(self):
        def get_number(obj):
            return obj['number']
        slips = json.loads(self.read({"current_boat": ""}))
        return sorted(slips, key=get_number, reverse=True)

    def get_slip(self, slip_id):
        search_obj = self.util.build_search_obj(slip_id)
        if not search_obj:
            return False
        return json.loads(self.read(search_obj))

    def find_slip(self, query):
        return self.read(query)

    def add_slip(self):
        max_number_agg = [
            {
                "$group": {
                    "_id": "0",
                    "max_number": {
                        "$max": "$number"
                    }
                }
            }
        ]
        aggregate_result = self.aggregate(max_number_agg)
        if len(aggregate_result) != 0:
            highest_number = aggregate_result[0]['max_number']
        else:
            highest_number = 0

        slip_obj = {
            "number": highest_number + 1,
            "current_boat": "",
            'arrival_date': '',
            'departure_history': []
        }
        return self.create(slip_obj)

    def take_slip_number(self, boat_id, slip_number):
        search_obj = {"number": slip_number}
        update_obj = {"$set": {
            "current_boat": boat_id,
            "arrival_date": datetime.now().strftime('%d-%m-%Y')
        }
        }
        return self.update(search_obj, update_obj)

    def clear_slip_number(self, slip_number):
        search_obj = {"number": slip_number}
        update_obj = {"$set": {
            "current_boat": "",
            "arrival_date": ""
        }
        }
        return self.update(search_obj, update_obj)

    def delete_slip(self, slip_id):
        search_obj = self.util.build_search_obj(slip_id)
        if not search_obj:
            return False
        return self.delete(search_obj)

    def clear_boat(self, boat_id):
        from controllers.boat import boat_controller as boats
        self.boats = boats()
        return self.boats.delete_boat(boat_id)
