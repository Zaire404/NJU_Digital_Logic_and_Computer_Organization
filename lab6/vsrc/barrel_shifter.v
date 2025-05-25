module BarrelShifter(
    input [31:0] din,
    input [4:0] shamt,
    input dir,
    input  [1:0] mode,
    output reg [31:0] dout
);
    localparam DIR_LEFT      = 1'b0;
    localparam DIR_RIGHT    = 1'b1;
    localparam MODE_LOGICAL    = 2'b00;
    localparam MODE_ARITHMETIC = 2'b01;
    localparam MODE_ROTATE     = 2'b10;

    always @(*) begin
        dout = din;
        if (dir == DIR_LEFT) begin
            case (mode)
                MODE_LOGICAL: begin
                    dout = shamt[0] ? {din[30:0], 1'b0} : dout;
                    dout = shamt[1] ? {dout[29:0], 2'b00} : dout;
                    dout = shamt[2] ? {dout[27:0], 4'b0000} : dout;
                    dout = shamt[3] ? {dout[23:0], 8'b00000000} : dout;
                    dout = shamt[4] ? {dout[15:0], 16'b0000000000000000} : dout;
                end
                MODE_ARITHMETIC: begin
                    dout = shamt[0] ? {dout[30:0], 1'b0} : dout;
                    dout = shamt[1] ? {dout[29:0], 2'b00} : dout;
                    dout = shamt[2] ? {dout[27:0], 4'b0000} : dout;
                    dout = shamt[3] ? {dout[23:0], 8'b00000000} : dout;
                    dout = shamt[4] ? {dout[15:0], 16'b0000000000000000} : dout;
                end
                MODE_ROTATE: begin
                    dout = shamt[0] ? {din[30:0], din[31]} : dout;
                    dout = shamt[1] ? {dout[29:0], dout[31:30]} : dout;
                    dout = shamt[2] ? {dout[27:0], dout[31:28]} : dout;
                    dout = shamt[3] ? {dout[23:0], dout[31:24]} : dout;
                    dout = shamt[4] ? {dout[15:0], dout[31:16]} : dout;
                end
                default: dout = din;
                endcase
        end else begin
            case (mode)
                MODE_LOGICAL: begin
                    dout = shamt[0] ? {1'b0, din[31:1]} : dout;
                    dout = shamt[1] ? {2'b00, dout[31:2]} : dout;
                    dout = shamt[2] ? {4'b0000, dout[31:4]} : dout;
                    dout = shamt[3] ? {8'b00000000, dout[31:8]} : dout;
                    dout = shamt[4] ? {16'b0000000000000000, dout[31:16]} : dout;
                end
                MODE_ARITHMETIC: begin
                    dout = shamt[0] ? {dout[31], dout[31:1]} : dout;
                    dout = shamt[1] ? {{2{dout[31]}}, dout[31:2]} : dout;
                    dout = shamt[2] ? {{4{dout[31]}}, dout[31:4]} : dout;
                    dout = shamt[3] ? {{8{dout[31]}}, dout[31:8]} : dout;
                    dout = shamt[4] ? {{16{dout[31]}}, dout[31:16]} : dout;
                end
                MODE_ROTATE: begin
                    dout = shamt[0] ? {din[0], din[31:1]} : dout;
                    dout = shamt[1] ? {dout[1:0], dout[31:2]} : dout;
                    dout = shamt[2] ? {dout[3:0], dout[31:4]} : dout;
                    dout = shamt[3] ? {dout[7:0], dout[31:8]} : dout;
                    dout = shamt[4] ? {dout[15:0], dout[31:16]} : dout;
                end
                default: dout = din;
            endcase
        end
    end
endmodule