import json


class boat_validator:
    def __init__(self):
        self.boat_types = ['catamaran', 'power', 'row', 'dingy', 'sail']
        self.restricted_fields = ['at_sea', 'docked_at', '_id']

    def post(self, boatObj):
        if (not boatObj['type'] or not boatObj['length'] or not boatObj['name']):
            return False
        if(boatObj['type'] not in self.boat_types):
            return False
        if type(boatObj['length']) is not int:
            return False
        if type(boatObj['name']) is not str:
            return False
        else:
            return True

    def patch(self, body_req):
        valid = True
        for i in body_req:
            if i in self.restricted_fields:
                return False
            if i == 'length' and not isinstance(body_req[i], int):
                return False
            if i == 'type' and not body_req[i] in self.boat_types:
                return False
            if i == 'name' and not isinstance(body_req[i], str):
                return False
        return valid
