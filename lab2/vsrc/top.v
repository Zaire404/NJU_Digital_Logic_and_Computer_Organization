module top(x, en, led, indicate, seg);
    input [7:0] x;
    input en;
    output reg [2:0] led;
    output reg indicate;
    output reg [6:0] seg;

    encode83 encode83_inst (
        .x(x),
        .en(en),
        .y(led),
        .indicate(indicate)
    );

    bcd7seg bcd7seg_inst (
        .b({1'b0,led}),
        .h(seg)
    );
endmodule