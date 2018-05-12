from pymongo import MongoClient
from bson.objectid import ObjectId
from utility.utility import utility

import pprint
import json
database = "HW2"
collection = "Ass2"


class crud_model(object):
    client = MongoClient()
    db = client[database]
    db = db[collection]
    util = utility()

    def __init__(self):
        pass

    def set_db_collection(self, db, collection):
        self.db = self.client[db]
        self.db = self.db[collection]
        print(self.db)

    def create(self, inserting_data):
        _id = self.db.insert_one(inserting_data).inserted_id
        mongo_result = self.db.find_one({"_id": _id})
        json_result = self.util.prep_json(mongo_result)
        return json.loads(json_result)

    def read(self, read_obj):
        return_array = []
        mongo_result = self.db.find(read_obj)
        for i in mongo_result:
            foo = self.util.prep_json(i)
            return_array.append(json.loads(foo))
        return json.dumps(return_array)

    def update(self, search_obj, update_obj):
        result = self.db.update_one(search_obj, update_obj).raw_result
        if result['ok'] == 1.0:
            mongo_result = self.db.find_one(search_obj)
            json_result = self.util.prep_json(mongo_result)
            return json.loads(json_result)
        else:
            return {"status": 503, "Msg": "Id not found"}

    def delete(self, search_obj):
        mongo_result = self.db.delete_one(search_obj).raw_result
        return mongo_result

    def aggregate(self, aggregation):
        mongo_result = self.db.aggregate(aggregation)
        return list(mongo_result)
