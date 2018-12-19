var DEGREE = 3;
var DEL = 0.001;
var bspline = require('b-spline');

function wiggle_points(p, rand_func, rand_data) {

  rand_func = ((typeof rand_func === "undefined") ? Math.random : rand_func);

  var pnts = [];
  var com = [0,0];

  if (p.length<4) { return []; }

  for (var idx=0; idx<p.length; idx++) {
    com[0] += p[idx][0];
    com[1] += p[idx][1];
  }

  com[0] /= p.length;
  com[1] /= p.length;

  for (var idx=0; idx<p.length; idx++) {
    //var ds = (range[1] - range[0])*Math.random() + range[0];
    var ds = rand_func(rand_data);
    var v = [ ds*(p[idx][0] - com[0]) + p[idx][0], ds*(p[idx][1] - com[1]) + p[idx][1] ];
    pnts.push(v);
  }

  return pnts;
}

function realize_bspline(pgn, del_t, deg) {
  var res_pgn = [];
  for (var dt = 0; dt < 1; dt += del_t) {
    var p = bspline(dt, deg, pgn);
    res_pgn.push(p);
  }
  return res_pgn;
}

function print_points(pnt, connect) {
  if (pnt.length < 1) { console.log(""); return ; }
  connect = ((typeof connect === "undefined") ? false : connect);

  var f = 1.0;
  for (var idx=0; idx<pnt.length; idx++) {
    console.log(f*pnt[idx][0], f*pnt[idx][1]);
  }
  if (connect) {
    console.log(pnt[0][0], pnt[0][1]);
  }
  console.log("");
}

//-------------------------------
//-------------------------------
//-------------------------------
//-------------------------------
//-------------------------------

var init_f = 1.0;
var pgns = [];
var pgn = [];

var n_pnt = 10;
for (var idx=0; idx<n_pnt; idx++) {
  var p = [];

  p[0] = init_f * Math.cos( 2.0 * Math.PI * idx / n_pnt );
  p[1] = init_f * Math.sin( 2.0 * Math.PI * idx / n_pnt );

  pgn.push(p);
}

function randn_bm() {
  var u = 0, v = 0;
  while(u === 0) { u = Math.random(); } //Converting [0,1) to (0,1)
  while(v === 0) { v = Math.random() };
  return Math.sqrt( -2.0 * Math.log( u ) ) * Math.cos( 2.0 * Math.PI * v );
}

function rand_func_u() {
  //var range = [0.01, 0.25];
  var range = [0.01, 0.3];
  return Math.random()*(range[1] - range[0]) + range[0];
}

function rand_func_a() {
  var x = randn_bm();

  var f = 0.1125;
  var m = 0.2;

  return (x*f) + m;
}

// https://stackoverflow.com/a/918827 by user gnovice
function rand_func_pl() {
  var range = [0.0001,0.5];

  var alpha = 0.0;
  var y = Math.random();
  var x = (Math.pow(range[1], alpha+1) - Math.pow(range[0], alpha+1)) * y + Math.pow(range[0], alpha+1);
  x = Math.pow(x, 1/(alpha+1));

  return x;
}

function rand_func() {
  var w0 = 1/1024;
  var w1 = 1/2;
  var v = w0*rand_func_u() + w1*rand_func_pl();
  return v;
}


pgns.push(wiggle_points(pgn, rand_func));

/*
var n_pgn = 5;
var n_pnt = 32;
var n_pnt_del = 2;
var skip_n = 1;
*/

/*
var n_pgn = 8;
var n_pnt = 16;
var n_pnt_del = 4;
var skip_n = 1;
*/

var n_pgn = 8;
var n_pnt = 128;
var n_pnt_del = 32;
var skip_n = 1;

for (var idx=0; idx<n_pgn; idx++) {

  // connect bezier spline onto itself
  //
  for (var ii=0; ii<(DEGREE); ii++) {
    pgns[idx].push( [ pgns[idx][ii][0], pgns[idx][ii][1] ] );
  }

  var disp_pnt = realize_bspline(pgns[idx], DEL, DEGREE);

  if (idx >= skip_n) {
    print_points(disp_pnt, true);
  }

  var control_idxs = [];
  for (var ii=0; ii<n_pnt; ii++) {
    control_idxs.push( Math.floor( disp_pnt.length * Math.random() ) );
  }
  control_idxs.sort(function(a,b) { return a-b; });

  var control_point = [];
  for (var ii=0; ii<n_pnt; ii++) {
    t_i = Math.floor(disp_pnt.length * ii / n_pnt);
    control_point.push( [ disp_pnt[t_i][0], disp_pnt[t_i][1] ] );

    //var t_i = control_idxs[ii];
    //control_point.push( [ disp_pnt[t_i][0], disp_pnt[t_i][1] ] );
  }

  pgns.push(wiggle_points(control_point, rand_func));

  n_pnt += n_pnt_del;
}


//console.log("\n\n");

//-----

/*
for (var t=0; t<1; t+=0.001) {
  var p = bspline(t, degree, points);
  console.log(p[0], p[1]);
}
*/



/*
var N = 100;
var points = [];

for (var ii=0; ii < N; ii++) {
  points.push([ ii, Math.sin(Math.PI * ii *0.2) ]);
}

for(var t=0; t<1; t+=0.001) {
  var p = bspline(t, degree, points);
  console.log(p[0], p[1]);
}
*/
