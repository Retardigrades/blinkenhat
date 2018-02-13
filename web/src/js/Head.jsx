import React, {Component} from 'react';

import AppBar from 'material-ui/AppBar';
import Toolbar from 'material-ui/Toolbar';
import Typography from 'material-ui/Typography';
import Button from 'material-ui/Button';
import IconButton from 'material-ui/IconButton';
import MenuIcon from 'material-ui-icons/Menu';

import {withStyles} from 'material-ui/styles';

const styles = {
  root: {
    width: '100%',
  },
  flex: {
    flex: 1,
  },
  menuButton: {
    marginLeft: -12,
    marginRight: 20,
  },
};

class Head extends Component {
  render() {
    const {classes} = this.props;

    return (
      <AppBar position="fixed">
        <Toolbar>
          <IconButton className={classes.menuButton} color="inherit" aria-label="Menu" onClick={this.props.showDrawer}>
            <MenuIcon/>
          </IconButton>
          <Typography type="title" color="inherit" className={classes.flex}>
            BlinkenHat
          </Typography>
          <Button color="inherit" onClick={this.props.onSave}>Save</Button>
        </Toolbar>
      </AppBar>
    );
  }
}

export default withStyles(styles)(Head)
