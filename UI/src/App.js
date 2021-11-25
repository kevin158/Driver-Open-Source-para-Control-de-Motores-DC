import React, { Component } from 'react';
// import logo from './logo.svg';
import './App.css';
import './style.css';

import {Switch,Route, Redirect, BrowserRouter as Router} from 'react-router-dom';
import PDIC from './components/pdic';

class App extends Component { 
  render(){
    return (
      <div className="App">
        <Router>
        <Switch>

          <Route exact path="/">
            <Redirect to='/PDIC' />
          </Route>

          <Route exact path="/PDIC">
              <PDIC />
           
          </Route>

        
        </Switch>
        </Router>
        {/* <RCA /> */}
         
      </div>
    );
  }
}

export default App;
