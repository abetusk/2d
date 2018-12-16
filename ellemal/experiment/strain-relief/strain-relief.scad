width = 18;
length = 22;
access_dw = 9;
access_dl = 7;

w2 = width/2;
l2 = length/2;
r = 2;

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

//v2
module strain_relief() {
  width=18;
  length = 22;
  w2=width/2;
  l2=length/2;
  
  d_s = 3*screw_r/2;
  
  difference() {
    
    union() {
      translate([0,-l2/2]) rounded_square(width-r,l2-r,r);
      translate([0, l2/2]) rounded_square(w2-r, l2-r, r);
      translate([0,l2-r]) rounded_square(width-r,2*d_s,r);
    }

    translate([-(w2-d_s),-(l2-d_s)]) circle(screw_r, $fn=FN);
    translate([ (w2-d_s),-(l2-d_s)]) circle(screw_r, $fn=FN);
    translate([-(w2-d_s),-d_s]) circle(screw_r, $fn=FN);
    translate([ (w2-d_s),-d_s]) circle(screw_r, $fn=FN);
    translate([-(w2-d_s), (l2-d_s)]) circle(screw_r, $fn=FN);
    translate([ (w2-d_s), (l2-d_s)]) circle(screw_r, $fn=FN);
  };
}


module strain_relief_v1() {
  
  difference() {
    rounded_square(width-r,length-r,r);
    translate([0, (length - access_dl)/2 - 2*screw_r])
      rounded_square(access_dw-r, access_dl-r, r);
    translate([-(w2-screw_r),-(l2-screw_r)]) circle(screw_r, $fn=FN);
    translate([ (w2-screw_r),-(l2-screw_r)]) circle(screw_r, $fn=FN);
    translate([-(w2-screw_r),0]) circle(screw_r, $fn=FN);
    translate([ (w2-screw_r),0]) circle(screw_r, $fn=FN);
    translate([-(w2-screw_r), (l2-screw_r)]) circle(screw_r, $fn=FN);
    translate([ (w2-screw_r), (l2-screw_r)]) circle(screw_r, $fn=FN);
  };
}

module strain_relief_old() {
  
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

dx=22;
dy=26;

strain_relief();
translate([dx, 0]) strain_relief();
translate([2*dx, 0]) strain_relief();
translate([3*dx, 0]) strain_relief();
translate([4*dx, 0]) strain_relief();


translate([0,dy]) strain_relief();
translate([dx, dy]) strain_relief();
translate([2*dx, dy]) strain_relief();
translate([3*dx, dy]) strain_relief();
translate([4*dx, dy]) strain_relief();

//difference() { circle(10);  translate([-10,-10]) circle(10);  translate([10,-10]) circle(10);};
