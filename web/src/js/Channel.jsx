import React, {Component} from 'react';

import Button from 'material-ui/Button';
import Divider from 'material-ui/Divider';
import AddIcon from 'material-ui-icons/Add';
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


const applyText = ["none", "upper", "lower", "both", "as one strip"];


function createDefault(effect, fxList) {
  const new_idx = (fxList.length === 0 ? 0 :
    Math.max.apply(null, fxList.map((v, i) => v.idx)) + 1);
  if (effect === "rainbow") {
    return {
      typ: "rainbow",
      idx: new_idx,
      cfg: {
        speed: 5000,
        apply: 1,
        coeff: 1.0
      }
    };
  }
  if (effect === "dot") {
    return {
      typ: "dot",
      idx: new_idx,
      cfg: {
        count: 3,
        speed: 6000,
        len: 10,
        hue: 0,
        color_speed: 4000,
        apply: 2,
        coeff: 1.0
      }
    };
  }
  if (effect === "twinkle") {
    return {
      typ: "twinkle",
      idx: new_idx,
      cfg: {
        count: 3,
        speed: 2000,
        fade: 500,
        color_mode: 0,
        hue: 0,
        apply: 2,
        coeff: 1.0
      }
    };
  }
}

function DotCfg(props) {
  return (
    <div>
      <SimpleSlider id="count" label="Number of dots" min={1} max={5} step={1} value={props.cfg.count}
                    onChange={props.updater("count")}
                    valueFormat={val => val}/>
      <SimpleSlider id="speed" label="Speed of dots" min={600} max={6000} step={200} value={props.cfg.speed}
                    onChange={props.updater("speed")}
                    valueFormat={val => val / 1000.0 + "sek"}/>
      <SimpleSlider id="len" label="Length of tail" min={1} max={15} step={1} value={props.cfg.len}
                    onChange={props.updater("len")}
                    valueFormat={val => val}/>
      <SimpleSlider id="hue" label="Start Hue value" min={0} max={255} step={10} value={props.cfg.hue}
                    onChange={props.updater("hue")}
                    valueFormat={val => val}/>
      <SimpleSlider id="color_speed" label="Speed of color change" min={600} max={6000} step={200}
                    value={props.cfg.color_speed}
                    onChange={props.updater("color_speed")}
                    valueFormat={val => val / 1000.0 + "sek"}/>
      <SimpleSlider id="apply" label="Apply To" min={0} max={4} step={1} value={props.cfg.apply}
                    onChange={props.updater("apply")}
                    valueFormat={val => applyText[val]}/>
      <SimpleSlider id="coeff" label="Visibility" min={0.1} max={1} step={0.1} value={props.cfg.coeff}
                    onChange={props.updater("coeff")}
                    valueFormat={val => val * 100 + "%"}/>
    </div>
  )
}

function RainbowCfg(props) {
  return (
    <div>
      <SimpleSlider id="speed" label="Speed" min={600} max={6000} step={200} value={props.cfg.speed}
                    onChange={props.updater("speed")}
                    valueFormat={val => val / 1000.0 + "sek"}/>
      <SimpleSlider id="apply" label="Apply to" min={0} max={4} step={1} value={props.cfg.apply}
                    onChange={props.updater("apply")}
                    valueFormat={val => applyText[val]}/>
      <SimpleSlider id="coeff" label="Visibility" min={0.1} max={1} step={0.1} value={props.cfg.coeff}
                    onChange={props.updater("coeff")}
                    valueFormat={val => val * 100 + "%"}/>
    </div>
  )
}

function Effect(props) {
  return (
    <PaperContainer headline={ "Effect: " + props.effect_data.typ} onRemove={props.deleter}>
      {props.effect_data.typ === 'rainbow' && <RainbowCfg updater={props.updater} cfg={props.effect_data.cfg}/>}
      {props.effect_data.typ === 'dot' && <DotCfg updater={props.updater} cfg={props.effect_data.cfg}/>}
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
          <MenuItem onClick={() => this.handleAdd("dot")}>Dot</MenuItem>
          <MenuItem onClick={() => this.handleAdd("rainbow")}>Rainbow</MenuItem>
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

  deleteEffect(id) {
    return event => {
      this.props.dataMangle(d => {
        const idx = d.effects.findIndex(v => v.idx === id);
        if (idx !== -1) {
          d.effects.splice(idx, 1);
        }
      });
    }
  }

  addEffect() {
    return name => {
      this.props.dataMangle(d => {
        const newItem = createDefault(name, d.effects);
        if (newItem !== undefined) {
          d.effects.push(newItem);
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
          <SimpleSlider id="leds" label="Number of LED" min={2} max={100} value={channel_data.leds}
                        onChange={this.changeData("leds")}
                        valueFormat={val => val + " LEDs"}/>
          <SimpleSlider id="gamma" label="Gamma Value" min={0.5} max={2} step={0.1} value={channel_data.gamma}
                        onChange={this.changeData("gamma")}
                        valueFormat={val => val}/>
        </PaperContainer>
        <Divider className={classes.divider}/>
        <AddMenu onAdd={this.addEffect()}/>

        {channel_data.effects.map((fx, idx) => (
          <Effect effect_data={fx} key={fx.idx}
                  updater={field => this.updateEffectData(fx.idx, field)}
                  deleter={this.deleteEffect(fx.idx)}/>
        ))}
      </Page>
    );
  }
}


export default withStyles(styles)(Channel)
