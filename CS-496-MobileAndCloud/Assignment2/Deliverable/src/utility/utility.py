from bson.objectid import ObjectId


class utility:
    def __init__(self):
        pass

    def prep_json(self, mongo_result):
        return self.clean_obj(mongo_result)

    def clean_obj(self, obj):
        obj['_id'] = str(obj['_id'])  # remove ObjectID type
        return self.string_to_json(obj)

    def string_to_json(self, data):
        for key in data:
            if type(data[key]) is bool:
                data[key] = str(data[key]).lower()
        return self.replace_quotes(data)

    def replace_quotes(self, string):
        return str(string).replace("\'", "\"")

    def build_query_string(self, query):
        query_obj = {}
        for i in query:
            try:
                query_obj[i] = int(query[i])
            except ValueError:
                query_obj[i] = query[i]
        return query_obj

    def build_search_obj(self, boat_id):
        try:
            obj = ObjectId(boat_id)
            return {
                "_id": obj
            }
        except:
            return False
