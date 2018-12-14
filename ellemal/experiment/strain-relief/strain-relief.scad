width = 12 + 2*2 + 2*2;
length = 50;
access_dw = 10;
access_dl = 8;

w2 = width/2;
l2 = length/2;
r = 4;

screw_r = 1;

FN=50;

module rounded_square(w,l,r) {
  w2= w/2;
  l2 = l/2;
  
  difference() {
    hull() {
      translate([-w2, -l2]) circle(r, $fn=FN);
      translate([ w2, -l2]) circle(r, $fn=FN);
      translate([ w2,  l2]) circle(r, $fn=FN);
      translate([-w2,  l2]) circle(r, $fn=FN);
    };
  };
    
}

module strain_relief() {
  
  recess_r = 2;
  //edge_r = (2*2 + 2*2)/2;
  edge_r = 2;
  difference() {
    rounded_square(width, length, r);

    // ridges... a little complicated because I did it as difference of
    // circles to round out the transition edge
    //
    translate([-w2-recess_r-edge_r, -2*screw_r])
    difference() {
      translate([0,        -2*recess_r]) circle(recess_r, $fn=FN);
      translate([recess_r,   -recess_r]) circle(recess_r, $fn=FN);
    };
    
    translate([-w2-recess_r-edge_r, -l2+2*screw_r+edge_r])
    difference() {
      translate([0,         0]) circle(recess_r, $fn=FN);
      translate([recess_r, -recess_r]) circle(recess_r, $fn=FN);
    };
    
    hull() {
      translate([-w2-4+recess_r,-2*(screw_r+recess_r+recess_r/2)]) circle(recess_r, $fn=FN);
      translate([-w2-4+recess_r,-(l2-3*recess_r)]) circle(recess_r, $fn=FN);
    };
    
    
    translate([w2+recess_r+edge_r, -2*screw_r])
    difference() {
      translate([0,        -2*recess_r]) circle(recess_r, $fn=FN);
      translate([-recess_r,   -recess_r]) circle(recess_r, $fn=FN);
    };
    
    translate([w2+recess_r+edge_r, -l2+2*screw_r+edge_r])
    difference() {
      translate([0,         0]) circle(recess_r, $fn=FN);
      translate([-recess_r, -recess_r]) circle(recess_r, $fn=FN);
    };
    hull() {
      translate([(w2+4-recess_r),-2*(screw_r+recess_r+recess_r/2)]) circle(recess_r, $fn=FN);
      translate([(w2+4-recess_r),-(l2-3*recess_r)]) circle(recess_r, $fn=FN);
    };

    // screw holes
    
    translate([-w2, -l2]) circle(screw_r, $fn=FN);
    translate([ w2, -l2]) circle(screw_r, $fn=FN);
    translate([ w2, 0]) circle(screw_r, $fn=FN);
    translate([-w2, 0]) circle(screw_r, $fn=FN);
    translate([-w2,  l2]) circle(screw_r, $fn=FN);
    translate([ w2,  l2]) circle(screw_r, $fn=FN);

    translate([0,access_dl/2]) rounded_square(access_dw, access_dl, 1);
    translate([0,l2 - 2*screw_r - access_dl/2]) rounded_square(access_dw, access_dl, 1); 
  };
}

strain_relief();
translate([w2+20, 0]) strain_relief();

//difference() { circle(10);  translate([-10,-10]) circle(10);  translate([10,-10]) circle(10);};
