module counter #(
    parameter WIDTH = 8
)(
    input logic clk,
    input logic rst,
    input logic en,
    output logic [WIDTH-1:0] count
);

always_ff @ (posedge clk or posedge rst)
    if (rst) count <= {WIDTH{1'b0}};                
    // else count <= count + {{WIDTH-1{1'b0}}, en};
    else count <= count + (en ? {{WIDTH-1{1'b0}}, 1'b1} : -{{WIDTH-1{1'b0}}, 1'b1});
endmodule
