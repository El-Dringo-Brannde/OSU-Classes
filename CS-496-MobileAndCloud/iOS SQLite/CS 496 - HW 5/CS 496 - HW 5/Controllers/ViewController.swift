import UIKit
import CoreLocation
import CoreData

class ViewController: UIViewController, UITableViewDelegate, CLLocationManagerDelegate, UITableViewDataSource {
    @IBOutlet weak var tableView: UITableView!
    @IBOutlet weak var Submit: UIButton!
    @IBOutlet weak var TextField: UITextField!
    @IBOutlet weak var LatVal: UILabel!
    @IBOutlet weak var LngVal: UILabel!
    @IBOutlet weak var LocationEnabled: UILabel!
    
    var entries: [NSManagedObject] = []
    let context = (UIApplication.shared.delegate as! AppDelegate).persistentContainer.viewContext
    
    private var CLocation = CLLocationManager();
    private var lat = "";
    private var lng = "";
    private var defaultLat = "44.5";
    private var defaultLng = "-123.2";
    
    override func viewDidLoad() {
        super.viewDidLoad()
        initCLocation()
        pullData()
    }

    
    func initCLocation() {
        CLocation.delegate = self
        CLocation.requestWhenInUseAuthorization()
        CLocation.desiredAccuracy = kCLLocationAccuracyBest
        CLocation.startUpdatingLocation()
    }
    
    func pullData() {
        do {
            entries = try context.fetch(Data.fetchRequest())
        } catch { print(error) }
    }
    
    
    @IBAction func AddData(_ sender: Any) {
        CLocation.requestLocation()
        let task = Data(context: context)
        task.value = TextField.text
        task.lat = lat
        task.lng = lng
        (UIApplication.shared.delegate as! AppDelegate).saveContext()
        TextField.text = "";
        pullData()
        tableView.reloadData()
    }
    
    // failed to get user location
    func locationManager(_ manager: CLLocationManager, didFailWithError error: Error) {
        print("Failed with error: \(error.localizedDescription)")
        let errorAlert = UIAlertView(title: "Error", message: "We couldn't get your permission.", delegate: nil, cancelButtonTitle: "Ok")
        errorAlert.show()
        LocationEnabled.text = "Location Disabled"
        lat = defaultLat
        lng = defaultLng
        LatVal.text = lat
        LngVal.text = lng
    }
    
    // successfully got user location
    func locationManager(_ manager: CLLocationManager, didUpdateLocations locations: [CLLocation]) {
        let newLocation = locations.last as! CLLocation
        print("Position: \(newLocation.coordinate.latitude), \(newLocation.coordinate.longitude)" )
        lat = String(newLocation.coordinate.latitude)
        LatVal.text = lat;
        lng = String(newLocation.coordinate.longitude)
        LngVal.text = lng
    }
    
    // number of rows in table view
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return self.entries.count
    }
    
    // create a cell for each table view row
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        pullData()
        
        guard let cell = self.tableView.dequeueReusableCell(withIdentifier: "cell") as? DataTableViewCell else { fatalError ("Hull Breach!") }
        let entry = entries[indexPath.row]
        
        cell.Data?.text =  entry.value(forKeyPath: "value") as? String
        cell.Lat.text = entry.value(forKeyPath: "lat") as? String
        cell.Lng.text = entry.value(forKeyPath: "lng") as? String
        
        return cell
    }
}
