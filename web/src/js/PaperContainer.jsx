import React from 'react';

import Paper from 'material-ui/Paper';
import Typography from 'material-ui/Typography';

import {withStyles} from 'material-ui/styles';
import IconButton from 'material-ui/IconButton';
import DeleteIcon from 'material-ui-icons/Delete';

const styles = theme => ({
  paper: {
    padding: 5,
    margin: 5,
    marginTop: 10,
    marginBottom: 5
  },
});


function PaperContainer(props) {
  const {classes} = props;

  let clStyle = {float: 'right'};
  return (
    <Paper className={classes.paper} elevation={4}>
      {props.onRemove !== undefined &&
      <IconButton color="secondary" onClick={props.onRemove} style={clStyle}><DeleteIcon/></IconButton>}
      <Typography type="subheading" gutterBottom>
        {props.headline}
      </Typography>
      {props.children}
    </Paper>
  );
}

export default withStyles(styles)(PaperContainer)
