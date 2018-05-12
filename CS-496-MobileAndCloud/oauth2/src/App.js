import React, { Component } from 'react';
import logo from './logo.svg';
import './App.css';
import {
    BrowserRouter as Router,
    Route,
    Link
} from 'react-router-dom'
import Button from 'muicss/lib/react/button';
import oauth from './components/oauth';

let hasher = require('rand-token');
let hash = hasher.generate(32)

class App extends Component {
    constructor() {
        super();
        this.state = {
            hash: hash
        }
    }


    getOauth() {
        window.location = "https://accounts.google.com/o/oauth2/v2/auth?" +
            "response_type=code" + "&" +
            "client_id=64007348932-5vc0hnoh6oi1g24tp1ghohtljceb50b5.apps.googleusercontent.com" + "&" +
            "redirect_uri=https://cs-496-191903.appspot.com/oauth" + "&" +
            "access_type=offline" + "&" +
            "scope=https://www.googleapis.com/auth/userinfo.email" + "&" +
            "state=" + hash + '&' +
            'prompt=consent'
    }


    render() {
        return (
            <div className="App">
                <header className="App-header">
                    <img src={logo} className="App-logo" alt="logo" />
                    <h1 className="App-title">Welcome to CS 496</h1>
                </header>
                <div className="App-intro">
                    <Router>
                        <div>
                            <br />
                            <Button variant="raised" onClick={this.getOauth}> Sign in with Google </Button>
                            <hr />
                            <Route path="/oauth" component={oauth} />
                        </div>
                    </Router>
                    State: {this.state.hash}
                </div>
            </div >
        );
    }
}

export default App;
