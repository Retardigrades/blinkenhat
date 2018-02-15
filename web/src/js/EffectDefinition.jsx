import React from 'react';

const applyText = ["none", "upper", "lower", "both", "as one strip"];
const colorModeText = ["white", "unicolor", "dynamic color"];


function makeSlider(label, min, max, step, dflt, format) {
  return {
    type: "slider",
    label: label,
    min: min,
    max: max,
    step: step,
    dflt: dflt,
    fmt: format
  };
}

function applySlider() {
  return makeSlider("Apply To", 0, 4, 1, 3, val => applyText[val]);
}

function visibleSlider() {
  return makeSlider("Visibility", 0, 1, 0.1, 1, val => (val * 100) + "%");
}

function speedSlider(label, min, max, step, dflt) {
  return makeSlider(label, min, max, step, dflt, val => (val / 1000.0) + "sek");
}


function hueSlider(label) {
  return makeSlider(label, 0, 255, 1, 0, val => "hue: " + val);
}

export const effects = {
  rainbow: {
    name: "Moving Rainbow",
    cfg: {
      speed: speedSlider("Speed", 200, 10000, 200, 5000),
      apply: applySlider(),
      coeff: visibleSlider()
    }
  },
  dot: {
    name: "Running Dot",
    cfg: {
      count: makeSlider("Number of rotating dots", 1, 10, 2, val => val + " dots"),
      speed: speedSlider("Speed of dots", 200, 10000, 200, 6000),
      len: makeSlider("Length of the tail", 1, 20, 1, 25, val => val + " pixels"),
      hue: hueSlider("Start color"),
      color_speed: speedSlider("Color change speed", 0, 10000, 200, 4000),
      apply: applySlider(),
      coeff: visibleSlider()
    }
  },
  twinkle: {
    name: "Twinkling Stars",
    cfg: {
      count: makeSlider("Number of stars", 1, 15, 1, 3, val => val + " stars"),
      speed: speedSlider("Avg. time between twinkles", 50, 5000, 50, 2000),
      fade: speedSlider("Time to fade in/out", 50, 2000, 50, 500),
      color_mode: makeSlider("Color mode", 0, 3, 1, 0, val => colorModeText[val]),
      hue: hueSlider("Color for unicolor mode"),
      apply: applySlider(),
      coeff: visibleSlider()
    }
  }
};
