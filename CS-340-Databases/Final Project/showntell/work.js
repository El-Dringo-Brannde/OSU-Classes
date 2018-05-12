<<<<<<< Updated upstream
/**
 * Created by brand_000 on 5/29/2017.
 */
google.load('visualization', '1', {
    packages: ['columnchart']
});
function initMap(){
    new Tipster();
}
class Tipster{
    constructor(){
        this.prevDeliveryAvg = 0;
        this.polyArray = [];
        this.cleanLatLng = [];
        this.path=[];
        this.dist = 0;
        this.map;
        this.initMap();
    }



    initMap(){
        var directionsDisplay = new google.maps.DirectionsRenderer;
        var directionsService = new google.maps.DirectionsService;

        this.map = new google.maps.Map(document.getElementById('map'), {
            zoom: 14,
            center: {
                lat: 44.5770402,
                lng: -123.2751523
            }
        });
        directionsDisplay.setMap(this.map);
        directionsDisplay.setPanel(document.getElementById('right-panel'));

        var trafficLayer = new google.maps.TrafficLayer();
        trafficLayer.setMap(this.map);

        var control = document.getElementById('floating-panel');
        control.style.display = 'block';
        this.map.controls[google.maps.ControlPosition.TOP_CENTER].push(control);
        let cur = this;
        $("#go").on('click', function(){
            cur.calculateAndDisplayRoute(directionsService, directionsDisplay);
            $.ajax({
                url: "/test",
                method: "POST",
                data: {
                    address: document.getElementById("to").value
                },
                success: (res) => {
                    cur.prevDeliveryAvg = parseFloat(res);
                }
            });
        });
    }

    calculateAndDisplayRoute(directionsService, directionsDisplay) {
        var start = document.getElementById('from').value;
        var end = document.getElementById('to').value;
        let cur = this;
        directionsService.route({
            origin: start,
            destination: end,
            provideRouteAlternatives: true,
            travelMode: "DRIVING",
            drivingOptions: {
                departureTime: new Date(Date.now())
            }

        }, function(result, status) {
            let colors = ['green', 'yellow', 'red'];
            if (status == google.maps.DirectionsStatus.OK) {
                for (var j = 0; j < result.routes.length; j++) {
                    cur.path = new google.maps.MVCArray();
                    cur.polyArray.push(new google.maps.Polyline({
                        map: cur.map,
                        strokeColor: colors[j],
                        strokeOpacity: 0.3,
                        strokeWeight: 5
                    }));

                    if (j == 0) cur.polyArray[0].setOptions({
                        strokeOpacity: 0.3
                    });
                    cur.polyArray[cur.polyArray.length - 1].setPath(cur.path);
                    for (var i = 0; i < cur.polyArray.length; i++) {
                        cur.polyArray[i].setOptions({
                            strokeOpacity: 0.3,
                            strokeColor: colors[i]
                        });
                        directionsDisplay.setOptions({
                            polylineOptions: {
                                strokeOpacity: 0.0
                            }
                        });
                    }
                    for (var i = 0, len = result.routes[j].overview_path.length; i < len; i++) {
                        cur.path.push(result.routes[j].overview_path[i]);
                    }
                }
            }
            directionsDisplay.setDirections(result);
            setTimeout(function() {
                let whichRoute;
                $($(".adp-listheader")[0].parentNode.parentNode.children).each(function(idx) {
                    $(this).on("click", function() {
                        $(cur.polyArray).each(function(i) {
                            if (cur.polyArray[idx - 1] === cur.polyArray[i]) {
                                whichRoute = i;
                                cur.polyArray[idx - 1].setOptions({
                                    strokeOpacity: 1
                                });
                                cur.dist = result.routes[i].legs[0].distance.text;
                                cur.processRoutes(result.routes[whichRoute]);
                                cur.prepChart(result, whichRoute);
                            } else
                                cur.polyArray[i].setOptions({
                                    strokeOpacity: 0.2
                                });

                        });
                    });
                });
            }, 500);
        });
    }


    processRoutes(results) {
        var lefts = 0;
        var rights = 0;
        document.getElementById("dist").innerHTML = "Distance: " + results.legs[0].distance.text;
        document.getElementById("dur").innerHTML = "Duration: " + results.legs[0].duration.text;
        document.getElementById("Traffic").innerHTML = "Time in traffic: " +
            (parseFloat(results.legs[0].duration_in_traffic.text) - parseFloat(results.legs[0].duration.text)).toString() +
            " Minutes";
        document.getElementById("dist").innerHTML = "Distance: " + results.legs[0].distance.text;

        for (var i = 0; i < results.legs[0].steps.length; i++) {
            if (results.legs[0].steps[i].instructions.search("left") !== -1)
                lefts++;
            else if (results.legs[0].steps[i].instructions.search("right") !== -1)
                rights++;
        }
        var dist = parseFloat(results.legs[0].distance.text);
        document.getElementById("LeftTurns").innerHTML = "Total Left Turns: " + (lefts).toString();
        document.getElementById("RightTurns").innerHTML = "Total Right Turns: " + (rights).toString();
        document.getElementById("TotalTurns").innerHTML = "Total Turns: " + results.legs[0].steps.length;
        var totalCost = (dist * 0.1 + dist * 0.05 + dist * 0.16);
        // ----------------------------- Costs ------------------------------
        if (this.searchPrev(dist, totalCost) === null) {
            document.getElementById("depreciation").innerHTML = "Depreciation (est. $0.16/mi): $" + (dist * 0.16).toString();
            document.getElementById("oil").innerHTML = "Cost of maintanence (est. @ 0.05/mi): $" + (dist * 0.05).toString();
            document.getElementById("gas").innerHTML = "Total Cost of gas(est. 25mpg @$2.50/gal): $" +
                (dist * 0.1).toString();
            document.getElementById("TotalCost").innerHTML = "Total Cost of Delivery: $" +
                totalCost.toString();
        }else{
            $("#carCost").hide();
            $("#chartdiv").html("");
            this.buildPieChart(dist * 0.16, dist * 0.05, dist * 0.1, totalCost)
        }

    }

    buildPieChart(depreciation, maintanence, gas, totalCost){
        let cur = this;

        let chartData = [
            { "sector": "Gas(est. 25mpg @$2.50/gal)", "size": gas},
            { "sector": "Depreciation", "size": depreciation},
            { "sector": "Maintenance", "size": maintanence},
            { "sector": "Profit", "size":parseFloat(this.prevDeliveryAvg) - parseFloat(totalCost)},
        ];


        var chart = AmCharts.makeChart( "chartdiv", {
            "type": "pie",
            "theme": "light",
            "dataProvider": chartData,
            "valueField": "size",
            "titleField": "sector",
            "pieX": 200,
            "minRadius": 100,
            "innerRadius": 40,
            "pullOutRadius": 5,
            "marginTop": 30,
            "titles": [{
                "text": "Estimated Tip ($" + (this.prevDeliveryAvg).toString() + ") Breakdown"
            }],
            "allLabels": [{
                "x":30,
                "y": "54%",
                "align": "center",
                "size": 25,
                "bold": true,
                "text": "$" +(parseFloat(this.prevDeliveryAvg) - parseFloat(totalCost)).toString(),
                "color": "#0c1355"
            }, {
                "x": 30,
                "y": "49%",
                "align": "center",
                "size": 15,
                "text": "Net Profit",
                "color": "#555"
            }],
            "export": {
                "enabled": true
            }
        });

    }


    searchPrev(dist, totalCost) {
        console.log(this.prevDeliveryAvg);
        if (this.prevDeliveryAvg !== null) {
            document.getElementById("est").innerHTML = "Estimated Profit: $" + (parseFloat(this.prevDeliveryAvg) - parseFloat(totalCost)).toString();
            return true;
        } else {
            document.getElementById("est").innerHTML = "(No known delivery Data)";
            return null;
        }
    }

    prepChart(result, whichRoute) {
        for (var i = 0; i < result.routes.length; i++) {
            var curPath = [];
            for (var j = 0; j < result.routes[i].overview_path.length; j++) {
                var lat = result.routes[i].overview_path[j].lat();
                var lng = result.routes[i].overview_path[j].lng();
                curPath.push({
                    lat,
                    lng
                });
            }
            this.cleanLatLng.push(curPath);
        }
        // Create an ElevationService.
        var elevator = new google.maps.ElevationService;
        // Draw the path, using the Visualization API and the Elevation service.
        this.displayPathElevation(this.cleanLatLng[whichRoute], elevator);
    }

    displayPathElevation(path, elevator) {
        // Create a PathElevationRequest object using this array.
        // Ask for 256 samples along that path.
        // Initiate the path request.
        let cur = this;
        elevator.getElevationAlongPath({
            'path': path,
            'samples': 128
        }, cur.plotElevation);
    }

    plotElevation(elevations, status) {
        var chartDiv = document.getElementById('elevation_chart');
        if (status !== 'OK') {
            // Show the error code inside the chartDiv.
            chartDiv.innerHTML = 'Cannot show elevation: request failed because ' +
                status;
            return;
        }
        // Create a new chart in the elevation_chart DIV.
        var chart = new google.visualization.ColumnChart(chartDiv);

        // Extract the data from which to populate the chart.
        // Because the samples are equidistant, the 'Sample'
        // column here does double duty as distance along the
        // X axis.
        var data = new google.visualization.DataTable();
        data.addColumn('string', 'dist');
        data.addColumn('number', 'Elevation');
        var totalEleChange = 0;
        let cur = this;
        for (var i = 0; i < elevations.length; i++) {
            if (i !== 0)
                totalEleChange += Math.abs(elevations[i].elevation - elevations[i - 1].elevation);
            if (i % 16 === 0)
                data.addRow([(parseFloat(cur.dist) / (elevations.length / i)).toString().slice(0, 4), elevations[i].elevation]);
            else
                data.addRow(["", elevations[i].elevation]);
        }
        document.getElementById("Elevation").innerHTML = "Total Elevation Change: " + (totalEleChange).toString().slice(0, 7) +
            " Meters";

        // Draw the chart using the data within its DIV.
        chart.draw(data, {
            legend: 'none',
            titleY: 'Elevation (m)',
            titleX: "Distance (mi)"
        });
    }
}

=======
google.load('visualization', '1', {
    packages: ['columnchart']
});
function initMap(){
    new Tipster();
}
class Tipster{
    constructor(){
        this.prevDeliveryAvg = 0;
        this.polyArray = [];
        this.cleanLatLng = [];
        this.path=[];
        this.dist = 0;
        this.map;
        this.selected = false;
        this.initMap();
    }

    initMap(){
        $("h4").hide();
        $("h5").hide();
        $("#route").hide();
        var directionsDisplay = new google.maps.DirectionsRenderer;
        var directionsService = new google.maps.DirectionsService;

        this.map = new google.maps.Map(document.getElementById('map'), {
            zoom: 14,
            center: {
                lat: 44.5770402,
                lng: -123.2751523
            }
        });
        directionsDisplay.setMap(this.map);
        directionsDisplay.setPanel(document.getElementById('right-panel'));

        var trafficLayer = new google.maps.TrafficLayer();
        trafficLayer.setMap(this.map);

        var control = document.getElementById('floating-panel');
        control.style.display = 'block';
        this.map.controls[google.maps.ControlPosition.TOP_CENTER].push(control);
        let cur = this;
        $("#go").on('click', function(){
            if (cur.selected === true)
                location.reload();
            cur.calculateAndDisplayRoute(directionsService, directionsDisplay);
            cur.selected = true;
            $.ajax({
                url: "/test",
                method: "POST",
                data: {
                    address: document.getElementById("to").value
                },
                success: (res) => {
                    cur.prevDeliveryAvg = parseFloat(res);
                }
            });
        });
    }

    calculateAndDisplayRoute(directionsService, directionsDisplay) {
        var start = document.getElementById('from').value;
        var end = document.getElementById('to').value;
        let cur = this;
        directionsService.route({
            origin: start,
            destination: end,
            provideRouteAlternatives: true,
            travelMode: "DRIVING",
            drivingOptions: {
                departureTime: new Date(Date.now())
            }
        }, function(result, status) {
            let colors = ['green', 'yellow', 'red'];
            if (status === google.maps.DirectionsStatus.OK) {
                for (var j = 0; j < result.routes.length; j++) {
                    cur.path = new google.maps.MVCArray();
                    cur.polyArray.push(new google.maps.Polyline({
                        map: cur.map,
                        strokeColor: colors[j],
                        strokeOpacity: 0.3,
                        strokeWeight: 5
                    }));

                    if (j === 0) cur.polyArray[0].setOptions({
                        strokeOpacity: 0.3
                    });
                    cur.polyArray[cur.polyArray.length - 1].setPath(cur.path);
                    for (var i = 0; i < cur.polyArray.length; i++) {
                        cur.polyArray[i].setOptions({
                            strokeOpacity: 0.3,
                            strokeColor: colors[i]
                        });
                        directionsDisplay.setOptions({
                            polylineOptions: {
                                strokeOpacity: 0.0
                            }
                        });
                    }
                    for (var i = 0, len = result.routes[j].overview_path.length; i < len; i++) {
                        cur.path.push(result.routes[j].overview_path[i]);
                    }
                }
            }
            directionsDisplay.setDirections(result);
            setTimeout(function() {
                let whichRoute;
                $($(".adp-listheader")[0].parentNode.parentNode.children).each(function(idx) {
                    $(this).on("click", function() {
                        $("#route").show();
                        $(cur.polyArray).each(function(i) {
                            if (cur.polyArray[idx - 1] === cur.polyArray[i]) {
                                whichRoute = i;
                                cur.polyArray[idx - 1].setOptions({
                                    strokeOpacity: 1
                                });
                                cur.dist = result.routes[i].legs[0].distance.text;
                                cur.processRoutes(result.routes[whichRoute]);
                                cur.prepChart(result, whichRoute);
                            } else
                                cur.polyArray[i].setOptions({
                                    strokeOpacity: 0.2
                                });

                        });
                    });
                });
            }, 500);
        });
    }



    processRoutes(results) {
        var lefts = 0;
        var rights = 0;
        $("#time").show();
        $("#dist1").show().css({
            margin: "0px",
            padding: "0px",
            top: "5%",
            left: "40%",
            position: "relative"
        });
        $("#time").css({
            margin: "0px",
            padding: "0px",
            top: "-15%",
            left: "40%",
            position: "relative"
        });
        document.getElementById("dist").innerHTML = results.legs[0].distance.text;
        document.getElementById("dur").innerHTML = results.legs[0].duration.text;
        document.getElementById("Traffic").innerHTML = "+ Traffic: " +
            (parseFloat(results.legs[0].duration_in_traffic.text) - parseFloat(results.legs[0].duration.text)).toString() +
            " Minutes";
        document.getElementById("dist").innerHTML = "Distance: " + results.legs[0].distance.text;

        for (var i = 0; i < results.legs[0].steps.length; i++) {
            if (results.legs[0].steps[i].instructions.search("left") !== -1)
                lefts++;
            else if (results.legs[0].steps[i].instructions.search("right") !== -1)
                rights++;
        }
        var dist = parseFloat(results.legs[0].distance.text);
        document.getElementById("LeftTurns").innerHTML = "Total Left Turns: " + (lefts).toString();
        document.getElementById("RightTurns").innerHTML = "Total Right Turns: " + (rights).toString();
        document.getElementById("TotalTurns").innerHTML = "Total Turns: " + results.legs[0].steps.length;
        var totalCost = (dist * 0.1 + dist * 0.05 + dist * 0.16);
        // ----------------------------- Costs ------------------------------
        if (this.searchPrev(dist, totalCost) === null) {
            $("h4").show();
            document.getElementById("depreciation").innerHTML = "Depreciation (est. $0.16/mi): $" + (dist * 0.16).toString().slice(0,6);
            document.getElementById("oil").innerHTML = "Cost of maintanence (est. @ 0.05/mi): $" + (dist * 0.05).toString().slice(0,6);
            document.getElementById("gas").innerHTML = "Total Cost of gas(est. 25mpg @$2.50/gal): $" +
                (dist * 0.1).toString().slice(0,6);
            document.getElementById("TotalCost").innerHTML = "Total Cost of Delivery: $" +
                totalCost.toString().slice(0,6);
        }else{
            $("#carCost").hide();
            $("#chartdiv").html("");
            this.buildPieChart(dist * 0.16, dist * 0.05, dist * 0.1, totalCost)
        }

    }

    buildPieChart(depreciation, maintanence, gas, totalCost){
        let chartData = [
            { "sector": "Gas(est. 25mpg @$2.50/gal)", "size": gas},
            { "sector": "Depreciation", "size": depreciation},
            { "sector": "Maintenance", "size": maintanence},
            { "sector": "Profit", "size":parseFloat(this.prevDeliveryAvg) - parseFloat(totalCost)},
        ];
        var chart = AmCharts.makeChart( "chartdiv", {
            "type": "pie",
            "theme": "light",
            "dataProvider": chartData,
            "valueField": "size",
            "titleField": "sector",
            "pieX": "40%",
            "minRadius": 100,
            "innerRadius": 40,
            "pullOutRadius": 5,
            "marginTop": 30,
            "titles": [{
                "text": "Estimated Tip ($" + (this.prevDeliveryAvg).toString() + ")"
            }],
            "allLabels": [{
                "x":"10%",
                "y": "54%",
                "align": "center",
                "size": 25,
                "bold": true,
                "text": "$" +(parseFloat(this.prevDeliveryAvg) - parseFloat(totalCost)).toString(),
                "color": "#0c1355"
            }, {
                "x": "10%",
                "y": "49%",
                "align": "center",
                "size": 15,
                "text": "Net Profit",
                "color": "#555"
            }]
        });
    }


    searchPrev(dist, totalCost) {
        console.log(isNaN(this.prevDeliveryAvg));
        if (this.prevDeliveryAvg !== null && !isNaN(this.prevDeliveryAvg)) {
            document.getElementById("est").innerHTML = "Estimated Profit: $" + (parseFloat(this.prevDeliveryAvg) - parseFloat(totalCost)).toString();
            return true;
        } else {
            document.getElementById("est").innerHTML = "(No known delivery Data)";
            return null;
        }
    }

    prepChart(result, whichRoute) {
        for (var i = 0; i < result.routes.length; i++) {
            var curPath = [];
            for (var j = 0; j < result.routes[i].overview_path.length; j++) {
                var lat = result.routes[i].overview_path[j].lat();
                var lng = result.routes[i].overview_path[j].lng();
                curPath.push({
                    lat,
                    lng
                });
            }
            this.cleanLatLng.push(curPath);
        }
        // Create an ElevationService.
        var elevator = new google.maps.ElevationService;
        // Draw the path, using the Visualization API and the Elevation service.
        this.displayPathElevation(this.cleanLatLng[whichRoute], elevator);
    }

    displayPathElevation(path, elevator) {
        // Create a PathElevationRequest object using this array.
        // Ask for 256 samples along that path.
        // Initiate the path request.
        let cur = this;
        elevator.getElevationAlongPath({
            'path': path,
            'samples': 128
        }, cur.plotElevation);
    }

    plotElevation(elevations, status) {
        var chartDiv = document.getElementById('elevation_chart');
        if (status !== 'OK') {
            // Show the error code inside the chartDiv.
            chartDiv.innerHTML = 'Cannot show elevation: request failed because ' +
                status;
            return;
        }
        // Create a new chart in the elevation_chart DIV.
        var chart = new google.visualization.ColumnChart(chartDiv);

        // Extract the data from which to populate the chart.
        // Because the samples are equidistant, the 'Sample'
        // column here does double duty as distance along the
        // X axis.
        var data = new google.visualization.DataTable();
        data.addColumn('string', 'dist');
        data.addColumn('number', 'Elevation');
        var totalEleChange = 0;
        let cur = this;
        for (var i = 0; i < elevations.length; i++) {
            if (i !== 0)
                totalEleChange += Math.abs(elevations[i].elevation - elevations[i - 1].elevation);
            if (i % 16 === 0)
                data.addRow([(parseFloat(cur.dist) / (elevations.length / i)).toString().slice(0, 4), elevations[i].elevation]);
            else
                data.addRow(["", elevations[i].elevation]);
        }
        document.getElementById("Elevation").innerHTML = "Total Elevation Change: " + (totalEleChange).toString().slice(0, 7) +
            " Meters";

        // Draw the chart using the data within its DIV.
        chart.draw(data, {
            legend: 'none',
            titleY: 'Elevation (m)',
            titleX: "Distance (mi)"
        });
    }
}

>>>>>>> Stashed changes
