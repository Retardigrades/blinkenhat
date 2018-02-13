import React, {Component} from 'react';

import Typography from 'material-ui/Typography';

import {withStyles} from 'material-ui/styles';

const styles = theme => ({
  root: {
    flexGrow: 1,
    padding: 5
  },
  headline: {
    marginTop: 50,
    padding: theme.spacing.unit,
    paddingTop: theme.spacing.unit * 2,
  }
});

function Page(props) {
  const {classes} = props;

  return (
    <div className={classes.root}>
      <div className={classes.headline}>
        <Typography type="headline" gutterBottom>
          {props.name}
        </Typography>
      </div>
      {props.children}
    </div>
  );
}

export default withStyles(styles)(Page)
