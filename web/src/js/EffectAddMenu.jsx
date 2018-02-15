import React, {Component} from 'react';

import Button from 'material-ui/Button';
import AddIcon from 'material-ui-icons/Add';
import Menu, {MenuItem} from 'material-ui/Menu';

import {withStyles} from 'material-ui/styles';

import {effects} from './EffectDefinition'


const styles = theme => ({});


class EffectAddMenu extends Component {
  constructor(props) {
    super(props);
    this.state = {
      anchorEl: null,
    };
  }

  handleClick(event) {
    this.setState({anchorEl: event.currentTarget});
  };

  handleClose() {
    this.setState({anchorEl: null});
  };

  handleAdd(name) {
    this.props.onAdd(name);
    this.handleClose();
  }

  render() {
    const {anchorEl} = this.state;

    return (
      <div>
        <Button raised
                aria-owns={anchorEl ? 'simple-menu' : null}
                aria-haspopup="true"
                onClick={e => this.handleClick(e)}
                color="primary">
          <AddIcon/> Add Effect
        </Button>
        <Menu
          id="simple-menu"
          anchorEl={anchorEl}
          open={Boolean(anchorEl)}
          onClose={() => this.handleClose()}>
          {Object.keys(effects).map(fx => (
            <MenuItem key={fx} onClick={() => this.handleAdd(fx)}>{effects[fx].name}</MenuItem>
          ))}
        </Menu>
      </div>
    );
  }
}


export default withStyles(styles)(EffectAddMenu);
