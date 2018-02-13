import React, {Component} from 'react';

import Button from 'material-ui/Button';
import Divider from 'material-ui/Divider';
import AddIcon from 'material-ui-icons/Add';
import Popover from 'material-ui/Popover';
import Menu, {MenuItem} from 'material-ui/Menu';


import SimpleSlider from './SimpleSlider'

import PaperContainer from './PaperContainer'
import Page from './Page';

import {withStyles} from 'material-ui/styles';

const styles = theme => ({
  fab: {
    position: 'absolute',
    bottom: theme.spacing.unit * 2,
    right: theme.spacing.unit * 2,
  },
  divider: {
    marginTop: theme.spacing.unit * 2,
    marginBottom: theme.spacing.unit * 2,
  }
});


function DotCfg(props) {
  return (
    <div>
      <SimpleSlider id="count" label="Number of dots" min={1} max={5} step={1} value={props.cfg.count}
                    onChange={props.updater("count")}
                    valueFormat={val => val}/>
      <SimpleSlider id="speed" label="Speed of dots" min={600} max={6000} step={200} value={props.cfg.speed}
                    onChange={props.updater("speed")}
                    valueFormat={val => val}/>
      <SimpleSlider id="len" label="Length of tail" min={1} max={15} step={1} value={props.cfg.len}
                    onChange={props.updater("len")}
                    valueFormat={val => val}/>
      <SimpleSlider id="hue" label="Start Hue value" min={0} max={255} step={10} value={props.cfg.hue}
                    onChange={props.updater("hue")}
                    valueFormat={val => val}/>
      <SimpleSlider id="color_speed" label="Speed of color change" min={600} max={6000} step={200}
                    value={props.cfg.color_speed}
                    onChange={props.updater("color_speed")}
                    valueFormat={val => val}/>
      <SimpleSlider id="apply" label="Apply To" min={0} max={3} step={1} value={props.cfg.apply}
                    onChange={props.updater("apply")}
                    valueFormat={val => val}/>
      <SimpleSlider id="coeff" label="Coeff" min={0} max={1} step={0.1} value={props.cfg.coeff}
                    onChange={props.updater("coeff")}
                    valueFormat={val => val}/>
    </div>
  )
}

function RainbowCfg(props) {
  return (
    <div>
      <SimpleSlider id="speed" label="Speed" min={600} max={6000} step={200} value={props.cfg.speed}
                    onChange={props.updater("speed")}
                    valueFormat={val => val}/>
      <SimpleSlider id="apply" label="Apply to" min={0} max={3} step={1} value={props.cfg.apply}
                    onChange={props.updater("apply")}
                    valueFormat={val => val}/>
      <SimpleSlider id="coeff" label="Coeff" min={0.1} max={1} step={0.1} value={props.cfg.coeff}
                    onChange={props.updater("coeff")}
                    valueFormat={val => val}/>
    </div>
  )
}

function Effect(props) {
  return (
    <PaperContainer headline={"Effect: " + props.effect_data.typ}>
      {props.effect_data.typ === 'rainbow' && <RainbowCfg updater={props.updater} cfg={props.effect_data.cfg}/>}
      {props.effect_data.typ === 'dot' && <DotCfg updater={props.updater} cfg={props.effect_data.cfg}/>}
      <Button>remove</Button>
    </PaperContainer>
  )
}

class AddMenu extends Component {
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

  render() {
    const {anchorEl} = this.state;

    return (
      <div>
        <Button raised
                aria-owns={anchorEl ? 'simple-menu' : null}
                aria-haspopup="true"
                onClick={e => this.handleClick(e)}
                color="primary"
        >
          <AddIcon/> Add Effect
        </Button>
        <Menu
          id="simple-menu"
          anchorEl={anchorEl}
          open={Boolean(anchorEl)}
          onClose={() => this.handleClose()}
        >
          <MenuItem onClick={() => this.handleClose()}>Dot</MenuItem>
          <MenuItem onClick={() => this.handleClose()}>Rainbow</MenuItem>
        </Menu>
      </div>
    );
  }
}


class Channel extends Component {

  changeData(field) {
    return event => {
      this.props.dataMangle(d => {
        d[field] = parseFloat(event.target.value);
      });
    }
  }

  updateEffectData(id, field) {
    return event => {
      this.props.dataMangle(d => {
        const idx = d.effects.findIndex(v => v.idx === id);
        if (idx !== -1) {
          d.effects[idx].cfg[field] = parseFloat(event.target.value);
        }
      });
    }
  }

  render() {
    const {classes, cfg_data} = this.props;
    const channel_data = cfg_data.channels[this.props.channel];

    return (
      <Page name={"Channel " + this.props.channel + " Settings"}>
        <PaperContainer headline="General channel settings">
          <SimpleSlider id="leds" label="Number of LED" min={30} max={100} value={channel_data.leds}
                        onChange={this.changeData("leds")}
                        valueFormat={val => val + " LEDs"}/>
          <SimpleSlider id="gamma" label="Gamma Value" min={0.5} max={2} step={0.1} value={channel_data.gamma}
                        onChange={this.changeData("gamma")}
                        valueFormat={val => val}/>
        </PaperContainer>
        <Divider className={classes.divider}/>
        <AddMenu/>

        {channel_data.effects.map((fx, idx) => (
          <Effect effect_data={fx} key={fx.idx} updater={field => this.updateEffectData(fx.idx, field)}/>
        ))}
      </Page>
    );
  }
}


export default withStyles(styles)(Channel)
