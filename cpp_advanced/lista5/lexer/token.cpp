#include "token.hpp"
#include "tokenType.hpp"

forward_list<Token> lexer(string &s) {
    TokenTypeDict token_type_dict;
    vector<Token> result;

    for(uint32_t pos = 0; pos < s.size();) {
        if(s[pos] == ' ') {
            pos++;
            continue;
        }

        auto t = token_type_dict.try_match_keyword(string_view(s).substr(pos)); // keyword
        if(!t) t = token_type_dict.try_match_value(string_view(s).substr(pos)); // val
        if(!t) t = token_type_dict.try_match_ident(string_view(s).substr(pos)); // ident

        if(!t) {
            throw invalid_argument("inapporpriate token at the begining: " + string(string_view(s).substr(pos)));
        } else {
            Token token = {
                t.value().first, 
                span<const char>(s.data() + pos, t.value().second)
            };
            result.push_back(token);
            pos += t.value().second;
        }
    }
    
    return forward_list(result.begin(), result.end());
}
