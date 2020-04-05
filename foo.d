struct nrvo {}

void main () @nrvo
{
    //Big f = selector(true);
    Big g = fwd();
}

Big fwd () @nrvo
{
    return fwd2();
}

Big fwd2 ()
{
    return fwd3();
}

Big fwd3 ()
{
    Big a = Big([1, 2, 3, 4, 5, 6, 7, 8]);
    return selector(true);
}

struct Big
{
    this(uint[8] val) { this.var = val; }
    this(uint c)      { this.var[] = c; }

    uint[8] var;
}

Big selector (bool check)
{
    Big a = Big([1, 2, 3, 4, 5, 6, 7, 8]);
    Big b = Big([42, 2, 3, 4, 5, 6, 7, 8]);
    return check ? a : b;
}
