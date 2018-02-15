import React, {Component} from 'react';

import SimpleSlider from './SimpleSlider'
import PaperContainer from './PaperContainer'

import {withStyles} from 'material-ui/styles';

import {effects} from './EffectDefinition'


const styles = theme => ({});


function FxConfigSlider(props) {
  return (
    <SimpleSlider id={props.typ} label={props.def.label}
                  min={props.def.min} max={props.def.max} step={props.def.step}
                  value={props.value}
                  onChange={props.updater(props.typ)}
                  valueFormat={props.def.fmt}/>
  )
}


function Effect(props) {
  const fx = props.effect_data;
  const fx_def = effects[fx.typ];

  const cfgs = Object.keys(fx_def.cfg);

  return (
    <PaperContainer headline={"Effect: " + fx_def.name} onRemove={props.deleter}>
      {cfgs.map(key => (
        <FxConfigSlider key={key} typ={key}
                        def={fx_def.cfg[key]}
                        value={fx.cfg[key]}
                        updater={props.updater}/>
      ))}
    </PaperContainer>
  );
}


export default withStyles(styles)(Effect);
