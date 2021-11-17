classdef decoder < handle
properties (Access = private)
    ptr;
    code;
end
methods
    function obj = decoder(m, usedBits, name, varargin)
        if nargin > 0 % nargin == 0 means that we are loading object
            obj.code = polar_decoder('code by used', m, usedBits);
            obj.ptr = polar_decoder('make decoder', name, obj.code, varargin{:});
        end
    end
    function delete(obj)
        polar_decoder('free decoder opt', obj.ptr);
        polar_decoder('free code', obj.code);
        obj.code = [];
        obj.ptr = [];
    end
    function result = step(obj, word)
        result = polar_decoder('decoder opt', obj.ptr, word);
    end
end
end

