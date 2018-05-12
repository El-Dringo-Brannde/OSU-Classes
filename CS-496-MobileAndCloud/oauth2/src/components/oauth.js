import React, { Component } from 'react';
import logo from './../logo.svg';
import { Route } from 'react-router';
let rp = require('request-promise')

class oauth extends Component {
    constructor() {
        super();
        this.code = window.location.href.split('?')[1] //get query string
            .split('&')[1] // get code query param
            .split('=')[1] // trim off 'code ='
            .slice(0, -1)
            .trim()
        this.stateSecret = window.location.href.split('?')[1] //get query string
            .split('&')[0] // get state query param
            .split('=')[1] // trim off 'code ='
        this.oauth;

        this.state = {
            time: new Date().toLocaleTimeString(),
            name: '',
            url: '',
            state: this.stateSecret
        }

        this.exchangeToken();
        this.updateTime();
    }

    updateTime() {
        setInterval(() => {
            this.setState({ time: new Date().toLocaleTimeString() })
        }, 1000)
    }

    async exchangeToken() {
        this.oauth = await rp({
            method: 'POST',
            uri: 'https://www.googleapis.com/oauth2/v4/token',
            headers: {
                'content-type': 'application/x-www-form-urlencoded'
            },
            form: {
                code: this.code,
                client_id: '64007348932-5vc0hnoh6oi1g24tp1ghohtljceb50b5.apps.googleusercontent.com',
                client_secret: 'tm8VjU3LEHCJcc2FntN38rN7',
                redirect_uri: 'https://cs-496-191903.appspot.com/oauth',
                'grant_type': 'authorization_code'
            }
        })
        this.oauth = JSON.parse(this.oauth)
        this.getData();
    }


    async getData() {
        this.user = await rp({
            method: 'GET',
            uri: 'https://www.googleapis.com/plus/v1/people/me',
            headers: {
                Authorization: 'Bearer ' + this.oauth.access_token
            }
        })
        this.user = JSON.parse(this.user)

        this.setState({ name: this.user.displayName })
        this.setState({ url: this.user.url })
    }


    render() {
        return (
            <div>
                <h1>It is {this.state.time}.</h1>
                <h3> Google+ name: {this.state.name} </h3>
                <br />
                <h3> Google+ url:
                    <a href={this.state.url}>
                        {this.state.url}
                    </a>
                </h3>
                <br />
                <h3> state from sign on: {this.state.state} </h3>
            </div>
        )
    }
}

export default oauth;