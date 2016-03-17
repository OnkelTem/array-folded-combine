<?php

/**
   * Combines nested arrays in a specific way.
   * For more information see: https://gist.github.com/OnkelTem/ddf341328960aa04a2ae
   *
   */

function array_folded_combine($x, $y) {
  // Check if array is a hash with one element: special case
  $key = NULL;
  if (is_array($x) && count($x) == 1 && array_keys($x) !== range(0, count($x) - 1)) {
    $key = array_keys($x)[0];
    $x = array_values($x)[0];
  }
  if (!is_array($x) && !is_array($y)) {
    // SCALAR × SCALAR = { SCALAR: SCALAR }
    if ($key) {
      return [$key => [$x => $y]];
    }
    else {
      return [$x => $y];
    }
  }
  else if (!is_array($x) && is_array($y)) {
    // SCALAR × [N] = { SCALAR: [N] }
    if ($key) {
      return [$key => [$x => $y]];
    }
    else {
      return [$x => $y];
    }
  }
  else if (is_array($x) && !is_array($y)) {
    // [N] × SCALAR = { [N]: SCALAR }
    throw new Exception('Error combining arrays: [N] × SCALAR: complex keys are not supported by PHP arrays.');
  }
  else if (is_array($x) && is_array($y) && count($x) == 1) {
    // [1] × [N] = [ 1 × N:1, 1 × N:2, ... , 1 × N:N ]
    $result = [];
    foreach($y as $y_item) {
      $result[] = array_folded_combine($x[0], $y_item);
    }
    if ($key) {
      return [ $key => $result];
    }
    else {
      return $result;
    }
  }
  else if (is_array($x) && is_array($y) && count($y) == 1 && count($x) > 1) {
    // [N] × [1] = [ N:1 × 1, N:2 × 1, ... , N:N × 1 ]
    throw new Exception('Error combining arrays: [N] × [1]: is not supported.');
  }
  else if (is_array($x) && is_array($y) && count($x) == count($y)) {
    // [N] × [N] = { N:1 × N:1, N:2 × N:2, ... , N:N × N:N }
    $result = [];
    foreach(array_keys($x) as $i) {
      $z = array_folded_combine($x[$i], $y[$i]);
      // Is numeric array?
      if (array_keys($z) === range(0, count($z) - 1)) {
        $result += array($z);
      }
      else {
        $result += $z;
      }
    }
    return $result;
  }
  else if (is_array($x) && is_array($y) && count($x) != count($y)) {
    // [M] × [N] = Undefined if M != N
    throw new Exception('Error combining arrays: [M] × [N]: amount of elements in arrays must be equal.');
  }
  else {
    throw new Exception('Error combining arrays: unknown error');
  }
}
