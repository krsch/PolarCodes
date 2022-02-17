classdef decoder < handle
properties (Access = private)
    ptr;
    code;
end
methods
    function obj = decoder(codeParams, name, varargin)
        % 'creeper', delta
        % 'fano', T, delta
        % 'flip fano', T, delta, approximationSnr, L
        % 'stack', L, D
        % 'stack opt', L, D
        if nargin > 0 % nargin == 0 means that we are loading object
            if numel(codeParams) == 2
                obj.code = polar_decoder('code by used', codeParams{:});
            elseif numel(codeParams) == 4
                obj.code = polar_decoder('code by rank', codeParams{:});
            else
                error 2 or 4 codeParams required
            end
            obj.ptr = polar_decoder(['make ' name], obj.code, varargin{:});
        end
    end
    function delete(obj)
        polar_decoder('free decoder', obj.ptr);
        polar_decoder('free code', obj.code);
        obj.code = [];
        obj.ptr = [];
    end
    function result = step(obj, word)
        result = polar_decoder('decode', obj.ptr, word);
    end
    function result = decode_flip(obj, word, flip_pos, flip_val)
        result = polar_decoder('decode flip', obj.ptr, word, flip_pos, flip_val);
    end
    function result = metric(obj)
        result = polar_decoder('get metric', obj.ptr);
    end
    function result = encode(obj, word)
        result = polar_decoder('encode', obj.code, word);
    end
    function [Iterations, Normilizer, Sums, Muls, Comps, Xors] = op_count(obj)
        [Iterations, Normilizer, Sums, Muls, Comps, Xors] = polar_decoder('get op count', obj.ptr);
    end
    function clear_op_count(obj)
        polar_decoder('clear op count', obj.ptr);
    end
end
end

