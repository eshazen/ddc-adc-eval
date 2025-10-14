//
// simple dark box for DDS test rig
//


mm = 25.4;
$fn = 32;
e = 0.1;

pcb_w = 2.7*mm;
pcb_l = 3.15*mm;

hole_dx = 2.3*mm;
hole_dy = 2.75*mm;
peg_dia = 0.155*mm;
so_hgt = 0.15*mm;
peg_len = 2.5;

box_w = 3.7*mm;
box_l = 3.5*mm;
box_t = 1.6;
box_h = 25;

module standoff_at( x, y, dia, hole, hgt, rot) {
    translate( [x, y, 0]) {
      rotate( [0, 0, rot]) {
      difference() {
	cylinder( d=dia, h=hgt);
	translate( [0, 0, -e])
	  cylinder( d=hole, h=hgt+2*e);
      }
    }
  }
}

module standoff_at_peg( x, y, dia, peg, hgt, peg_len) {
  translate( [x, y, 0]) {
    cylinder( d=dia, h=hgt);
    translate( [0, 0, hgt-e])
      cylinder( d=peg, h=peg_len+e);
  }
}

module standoffs() {
  standoff_at_peg( 0, hole_dy, 0.25*mm, peg_dia, so_hgt, peg_len);
  standoff_at_peg( 0, 0, 0.25*mm, peg_dia, so_hgt, peg_len);
  standoff_at_peg( hole_dx, 0, 0.25*mm, peg_dia, so_hgt, peg_len);
  standoff_at_peg( hole_dx, hole_dy, 0.25*mm, peg_dia, so_hgt, peg_len);
  //  translate( [-0.2*mm, -0.2*mm, 0]) color("red") cube( [pcb_w, pcb_l, 1.6]);
}

module box( wid, leng, hgt, thick) {
  difference() {
    cube( [wid, leng, hgt]);
    translate( [thick, thick, thick])
      cube( [wid-2*thick, leng-2*thick, hgt]);
    rotate( [90, 0, 90])
      translate( [box_l/2, box_h/2, box_l])
      cylinder( d=0.25*mm, h=10);
  }
}

module box_assy() {
  box( box_w, box_l, box_h, box_t);
  translate( [10, (box_w-pcb_w)/2-0.2*mm+box_t, box_t-e])
    standoffs();
}

module lid() {
  cube( [box_w, box_l, box_t]);
  translate( [box_t, box_t, -box_t+e])
    cube( [box_w-box_t*2, box_l-box_t*2, box_t]);
}

 box_assy();
// rotate( [0, 180, 0]) lid();

