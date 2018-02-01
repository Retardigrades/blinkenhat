/**
 * In this file, we create a React component
 * which incorporates components provided by Material-UI.
 */
import React, {Component} from 'react';
import Reboot from 'material-ui/Reboot';
import {MuiThemeProvider, createMuiTheme} from 'material-ui/styles';


import {withStyles} from 'material-ui/styles';

import Head from './Head';
import Navigation from './Navigation';
import Upgrade from './Upgrade';
import WiFi from './WiFi'


const styles = {
  root: {
    width: '100%',
  }
};

const theme = createMuiTheme({
  palette: {
    type: 'dark', // Switching the dark mode on is a single property value change.
  },
});

class Main extends Component {

  constructor(props) {
    super(props);
    this.state = {
      drawer: true,
      view: 0,
      global_data: {
        sta_ssid: "",
        sta_passwd: "",
        ap_ssid: "",
        ap_passwd: ""
      }
    }
  }

  toggleDrawer(open) {
    this.setState({drawer: open});
  }

  changeView(viewNum) {
    this.setState({
      view: viewNum,
      drawer: false
    });
  }

  setGlobalData(field, value) {
    const update = {};
    update[field] = value;
    this.setState({global_data: Object.assign({}, this.state.global_data, update)})
  }

  render() {
    const {classes} = this.props;
    const view = this.state.view;

    return (
      <div className={classes.root}>
        <MuiThemeProvider theme={theme}>
          <Reboot/>
          <Navigation onViewChange={n => this.changeView(n)} hideDrawer={() => this.toggleDrawer(false)}
                      open={this.state.drawer}/>
          <Head showDrawer={() => this.toggleDrawer(true)}/>
          {view === 3 &&
          <WiFi cfg_data={this.state.global_data} onDataChange={(field, val) => this.setGlobalData(field, val)}/>}
          {view === 4 && <Upgrade/>}
        </MuiThemeProvider>
      </div>
    );
  }
}

export default withStyles(styles)(Main);