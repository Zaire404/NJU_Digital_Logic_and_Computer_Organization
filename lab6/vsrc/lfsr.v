module lfsr (
    input clk,
    input reset,
    output reg [7:0] out
);

    wire feedback_bit;
    assign feedback_bit = out[4] ^ out[3] ^ out[2] ^ out[0];
    always @(posedge clk or posedge reset) begin
        if (reset) begin
            out <= 8'b00000001;
        end else begin
            out <= {feedback_bit, out[7:1]};
        end
    end
endmodule