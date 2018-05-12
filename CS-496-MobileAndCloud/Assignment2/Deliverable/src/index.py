from bottle import run
from routes.boat import boat_routes
from routes.slip import slip_routes

if __name__ == "__main__":
    boat_routes()  # Declare routes
    slip_routes()
    run(host='0.0.0.0', port=12345, debug=True)
