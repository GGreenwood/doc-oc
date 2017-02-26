// All units are in mm

// Circle approximation constant
$fn=80;

// Epsilon value
e = 0.01;

// Base height
b_h= 5;
// Base width
b_w= 130;

// Fan screw distance
f_screw = 104.775;
// Fan circular diameter
f_d = 110;

// Shroud thickness
s_t = 10;
// Shroud height
s_h = 50;
// Shroud width
s_w = 4;
// Shroud top
s_t = 50;

// Driver board width
d_w = 37.4;
// Driver board height
d_h = 68.2;

// Outer shroud wall
module shroud1() {
	hull(){
		translate([-f_d/2, -s_t/2, s_h]) {
			cube([s_t,s_t,e]);
		}

        translate([-f_d/2, 0, 0])
            linear_extrude(height=s_h, scale=.25)
                translate([f_d/2, 0, 0])
                    circle(d=f_d);

        translate([-f_d/2 - 3, -s_t/2, 0])
            cube([s_t/2, s_t, s_h]);
	}
}

// Inner shroud wall
module shroud2() {
	hull(){
		translate([-f_d/2+s_w, -s_t/2+s_w, s_h]) {
			cube([s_t-s_w*2,s_t-s_w*2,2*e]);
		}
        translate([-f_d/2, 0, -e])
            linear_extrude(height=s_h, scale=.25)
                translate([f_d/2, 0, 0])
                    circle(d=f_d-s_w/2);
	}
}

union() {

    difference() {
        cube([b_w, b_w, b_h]);

        translate([(b_w - f_screw)/2, (b_w - f_screw)/2, -e])
            cylinder(d=6.5, h=b_h+2*e);
        translate([(b_w + f_screw)/2, (b_w - f_screw)/2, -e])
            cylinder(d=6.5, h=b_h+2*e);
        translate([(b_w - f_screw)/2, (b_w + f_screw)/2, -e])
            cylinder(d=6.5, h=b_h+2*e);
        translate([(b_w + f_screw)/2, (b_w + f_screw)/2, -e])
            cylinder(d=6.5, h=b_h+2*e);

        translate([b_w/2, b_w/2, -e]) {
            cylinder(d=f_d - 8, h=b_h+2*e);
        }
    }

    translate([b_w/2+3, b_w/2, 0]) {
        difference() {
            shroud1();
            shroud2();
            cylinder(d=f_d, h=e, center=true);
        }
    }

    translate([10, f_d/2-15, s_h]) {
        difference() {
            cube([5.5, s_t, 75]);
            translate([-e, (s_t-d_w)/2, (75-d_h)/2]) {
                rotate([0, 90, 0]) {
                    translate([0, 0, 0])
                        cylinder(d=4.5, h=10);
                    translate([-d_h, 0, 0])
                        cylinder(d=4.5, h=10);
                    translate([0, d_w, 0])
                        cylinder(d=4.5, h=10);
                    translate([-d_h, d_w, 0])
                        cylinder(d=4.5, h=10);
                }
            }
        }
    }

    translate([10, b_w/2 + 2, 0]) {
        rotate([0, 0, 180]) {
            translate([0,8,0])
                linear_extrude(height = 120, scale=[e, 1])
                    square([10,4]);
            translate([0,-8,0])
                linear_extrude(height = 120, scale=[e, 1])
                    square([10,4]);
        }
    }
}
