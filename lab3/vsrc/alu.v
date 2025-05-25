module alu(
    input [3:0] a,
    input [3:0] b,
    input [2:0] op,
    output reg [3:0] result,
    output reg cf,
    output reg zf,
    output reg of
);
    reg [3:0] temp;
    always @(*) begin
        zf = 0;
        cf = 0;
        of = 0;
        result = 0;
        temp = 0;
        casez (op)
            3'b00z: begin // Add and Sub
                temp = b ^ {4{op[0]}};
                {cf, result} = a + temp + {3'b0,op[0]};
                of = (a[3] == temp[3]) && (result[3] != a[3]);
            end
            3'b010: begin // Not A
                result = ~a;
                cf = 0;
                of = 0;
            end
            3'b011: begin // And
                result = a & b;
                cf = 0;
                of = 0;
            end
            3'b100: begin // Or
                result = a | b;
                cf = 0;
                of = 0;
            end
            3'b101: begin // Xor
                result = a ^ b;
                cf = 0;
                of = 0;
            end
            3'b110: begin // Less than
                // a - b
                temp = b ^ 4'b1111;
                {cf, result} = a + temp + 1;
                of = (a[3] == temp[3]) && (result[3] != a[3]);
                // 7 - （-8）
                // 0111 - 1000
                // temp = 0111
                if (of) result = a[3] ? 1 : 0; // a is negative, result is 1 if a < b
                else result = (result == 0) ? 0:{3'b0, result[3]};
            end
            3'b111: begin // Equal
                result = (a == b) ? 1 : 0;
                cf = 0;
                of = 0;
            end
            default: begin // Nop
                result = 0;
                cf = 0;
                of = 0;
                zf = 0;
            end
        endcase
        zf = ~(| result);
    end
endmodule