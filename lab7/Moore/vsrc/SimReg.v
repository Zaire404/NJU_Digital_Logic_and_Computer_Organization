module SimReg #(parameter WIDTH = 8,parameter INIT_VALUE = 0) (
    input clk, reset,
    input [WIDTH-1:0] state_din,
    input state_wen,
    output reg [WIDTH-1:0] state_dout
);

always @(posedge clk) begin
    if (reset) begin
        state_dout <= INIT_VALUE;
    end else if (state_wen) begin
        state_dout <= state_din;
    end else begin
        state_dout <= state_dout;
    end

end

endmodule