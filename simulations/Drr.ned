package drr.simulations;

import drr.Source;
import drr.Sink;
import drr.Cdrr;

network drr
{
    parameters:
        int numSources = default(2);
    submodules:
        gen[numSources]: Source {
            parameters:
                srcAddress = index;
                @display("p=89,61");
        }
//        gen2: Source {
//            parameters:
//                @display("p=89,159");
//        }
        cdrr: Cdrr {
            parameters:
                @display("p=209,100");
        }
        sink[numSources]: Sink {
            parameters:
                @display("p=323,61");
        }
//        sink2: Sink {
//            parameters:
//                @display("p=329,159");
//        }
    connections:
        for i = 0..numSources-1 {
        	gen[i].out --> cdrr.in++;
//        gen2.out --> fifo.in++;
        	cdrr.out++ --> sink[i].in;
//        fifo.out++ --> sink2.in;
        }
}
