using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.Security.Cryptography;

namespace K9ngine_v1_editor
{
    static class Hasher
    {
        static public Int32 Hash(String value)
        {
            //TODO: Implement my own hasher, the same that I will use in C++ engine.
            return value.GetHashCode();
        }
    }
}
