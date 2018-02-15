import React, {Component} from 'react';

import Divider from 'material-ui/Divider';

import {withStyles} from 'material-ui/styles';

import SimpleSlider from './SimpleSlider'
import PaperContainer from './PaperContainer'
import Page from './Page';
import Effect from './Effect'
import EffectAddMenu from './EffectAddMenu'
import {effects} from "./EffectDefinition"


const styles = theme => ({
  divider: {
    marginTop: theme.spacing.unit * 2,
    marginBottom: theme.spacing.unit * 2,
  }
});


function createDefault(effect, fxList) {
  const new_idx = (fxList.length === 0 ? 0 :
    Math.max.apply(null, fxList.map((v, i) => v.idx)) + 1);

  const fx = {
    typ: effect,
    idx: new_idx,
    cfg: {}
  };

  for (let key in effects[effect].cfg) {
    fx.cfg[key] = effects[effect].cfg[key].dflt;
  }

  return fx;
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
        <EffectAddMenu onAdd={this.addEffect()}/>

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
