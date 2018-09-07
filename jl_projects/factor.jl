function fact(num::Int)
    function private_fact(n::Int, tmp::Int)
        n == 0 && return tmp
        return private_fact(n-1, n*tmp)
    end
    num >= 0 || throw(DomainError(num, "argument must be non-negative")
    private_fact(num, 1)
end

