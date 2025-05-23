module encode83(x, en, y, indicate);
    input [7:0] x;
    input en;
    output reg [2:0] y;
    output reg indicate;

    always @(x, en) begin
        y = 3'b000;
        indicate = 1'b0;
        if (en) begin
            if (x != 0) begin
            indicate = 1'b1;
            for (int i = 0; i < 8; i++) 
                if (x[i]) y = i[2:0];
            end
            else indicate = 1'b0;
        end
    end
endmodule