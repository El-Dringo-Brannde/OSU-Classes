

class errors:
    def __init__(self):
        pass

    def invalid_boat_id(self):
        return {'Status': 503, 'Message': 'Invalid boat_id'}

    def invalid_slip_id(self):
        return {'Status': 503, 'Message': 'Invalid slip_id'}

    def bad_request(self):
        return {"Status": 503, "Message": "Bad Request"}

    def already_docked(self):
        return {'status': 503, 'Message': 'Boat already docked.'}

    def no_spots(self):
        return {'status': 403, 'Message': 'No spots available'}

    def already_at_sea(self):
        return {'status': 503, 'Message': 'Boat already at sea.'}

    def cant_modify_slip(self):
        return {'status': 403, 'Message': 'Cant modify slip, instead remove ship docked and add desired ship to change current boat and arrival'}

    def cant_modify_boat(self):
        return {'status': 403, 'Message': 'You cant replace an entire boat...'}
