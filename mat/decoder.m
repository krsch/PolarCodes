classdef decoder < handle
properties (Access = private)
    ptr;
    code;
end
methods
    function obj = decoder(m, usedBits, name, varargin)
        % 'creeper', delta
        % 'fano', T, delta
        % 'flip fano', T, delta, approximationSnr, L
        % 'stack', L, D
        % 'stack opt', L, D
        if nargin > 0 % nargin == 0 means that we are loading object
            obj.code = polar_decoder('code by used', m, usedBits);
            obj.ptr = polar_decoder(['make ' name], obj.code, varargin{:});
        end
    end
    function delete(obj)
        polar_decoder('free decoder opt', obj.ptr);
        polar_decoder('free code', obj.code);
        obj.code = [];
        obj.ptr = [];
    end
    function result = step(obj, word)
        result = polar_decoder('decode', obj.ptr, word);
    end
    function result = encode(obj, word)
        result = polar_decoder('encode', obj.ptr, word);
    end
    function [Iterations, Normilizer, Sums, Muls, Comps, Xors] = op_count(obj)
        [Iterations, Normilizer, Sums, Muls, Comps, Xors] = polar_decoder('get op count', obj.ptr);
    end
    function clear_op_count(obj)
        polar_decoder('clear op count', obj.ptr);
    end
end
end

