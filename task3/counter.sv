module counter #(
    parameter WIDTH = 8
)(
    input  logic clk,
    input  logic rst,
    input  logic ld,
    input  logic [WIDTH-1:0] v,
    output logic [WIDTH-1:0] count
);

always_ff @ (posedge clk)
    if (rst) count <= {WIDTH{1'b0}};
    // else count <= ld ? v : count + {{WIDTH-1{1'b0}},1'b1};
    else if (ld) count + {{WIDTH-1{1'b0}},1'b1};
endmodule
