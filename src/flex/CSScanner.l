/**
 * A C# token descriptions written in correspondance to C# 6 language
 * specification found here: https://github.com/ljw1004/csharpspec
 * , where the exact grammars for tokens are given
 */


/**
 * Section 10.1.5.1 of the 3.0.2 Bison Manual says the
 * following should work:
 * yylval.build( yytext );
 * but it doesn't.
 * ref: http://goo.gl/KLn0w2
 * yylval->build< std::string >( yytext );
 * return( token::WORD );
 *
 * // Update line number
 * loc->lines();
 * return( token::NEWLINE );
 */



%{
/* C++ string header, for string ops below */
#include <string>

/* Implementation of yyFlexScanner */
#include "../flex/CSScanner.hpp"
#undef  YY_DECL
#define YY_DECL int Metrics::CSScanner::yylex( Metrics::CSParser::semantic_type * const lval, Metrics::CSParser::location_type *loc )

/* typedef to make the returns for the tokens shorter */
using token = Metrics::CSParser::token;

/* define yyterminate as this instead of NULL */
#define yyterminate() return( token::END )

/* msvc2010 requires that we exclude this header file. */
#define YY_NO_UNISTD_H

/* update _location on matching */
#define YY_USER_ACTION loc->step(); loc->columns(yyleng);
%}



%option debug
%option nodefault
%option yyclass="Metrics::CSScanner"
%option noyywrap
%option c++




%%
%{                              /** Code executed at the beginning of yylex **/
                                yylval = lval;
%}




[\n]|(\r\n)                     {
                                    loc->lines();
                                    // return( token::NEW_LINE );
                                }

"#"                             {   /* Pre-processor */
                                    return( token::HASH );
                                }

define                          {
                                    return( token::DEFINE );
                                }

undef                           {
                                    return( token::UNDEF );
                                }




abstract                        {   /* Keywords */
                                    return( token::ABSTRACT );
                                }

add                             {
                                    return( token::ADD );
                                }

alias                           {
                                    return( token::ALIAS );
                                }

as                              {
                                    return( token::AS );
                                }

ascending                       {
                                    return( token::ASCENDING );
                                }

assembly                        {
                                    return( token::ASSEMBLY );
                                }

await                           {
                                    return( token::AWAIT );
                                }

base                            {
                                    return( token::BASE );
                                }

bool                            {
                                    return( token::BOOL );
                                }

break                           {
                                    return( token::BREAK );
                                }

by                              {
                                    return( token::BY );
                                }

byte                            {
                                    return( token::BYTE );
                                }

case                            {
                                    return( token::CASE );
                                }

catch                           {
                                    return( token::CATCH );
                                }

char                            {
                                    return( token::CHAR );
                                }

checked                         {
                                    return( token::CHECKED );
                                }

class                           {
                                    return( token::CLASS );
                                }

const                           {
                                    return( token::CONST );
                                }

continue                        {
                                    return( token::CONTINUE );
                                }

decimal                         {
                                    return( token::DECIMAL );
                                }

default                         {
                                    return( token::DEFAULT );
                                }

delegate                        {
                                    return( token::DELEGATE );
                                }

descending                      {
                                    return( token::DESCENDING );
                                }

do                              {
                                    return( token::DO );
                                }

double                          {
                                    return( token::DOUBLE );
                                }

dynamic                         {
                                    return( token::DYNAMIC );
                                }

else                            {
                                    return( token::ELSE );
                                }

enum                            {
                                    return( token::ENUM );
                                }

equals                          {
                                    return( token::EQUALS );
                                }

event                           {
                                    return( token::EVENT );
                                }

explicit                        {
                                    return( token::EXPLICIT );
                                }

extern                          {
                                    return( token::EXTERN );
                                }

false                           {
                                    return( token::FALSE );
                                }

field                           {
                                    return( token:: FIELD );
                                }

finally                         {
                                    return( token::FINALLY );
                                }

fixed                           {
                                    return( token::FIXED );
                                }

float                           {
                                    return( token::FLOAT );
                                }

for                             {
                                    return( token::FOR );
                                }

foreach                         {
                                    return( token::FOREACH );
                                }

from                            {
                                    return( token::FROM );
                                }

get                             {
                                    return( token::GET );
                                }

goto                            {
                                    return( token::GOTO );
                                }

group                           {
                                    return( token::GROUP );
                                }

if                              {
                                    return( token::IF );
                                }

implicit                        {
                                    return( token::IMPLICIT );
                                }

in                              {
                                    return( token::IN );
                                }

int                             {
                                    return( token::INT );
                                }

into                            {
                                    return( token::INTO );
                                }

interface                       {
                                    return( token::INTERFACE );
                                }

internal                        {
                                    return( token::INTERNAL );
                                }

is                              {
                                    return( token::IS );
                                }

join                            {
                                    return( token::JOIN );
                                }

let                             {
                                    return( token::LET );
                                }

lock                            {
                                    return( token::LOCK );
                                }

long                            {
                                    return( token::LONG );
                                }

method                          {
                                    return( token::METHOD );
                                }

module                          {
                                    return( token::MODULE );
                                }

nameof                          {
                                    return( token::NAMEOF );
                                }

namespace                       {
                                    return( token::NAMESPACE );
                                }

new                             {
                                    return( token::NEW );
                                }

null                            {
                                    return( token::Null );
                                }

object                          {
                                    return( token::OBJECT );
                                }

on                              {
                                    return( token::ON );
                                }

operator                        {
                                    return( token::OPERATOR );
                                }

orderby                         {
                                    return( token::ORDERBY );
                                }

out                             {
                                    return( token::OUT );
                                }

override                        {
                                    return( token::OVERRIDE );
                                }

param                           {
                                    return( token::PARAM );
                                }

params                          {
                                    return( token::PARAMS );
                                }

partial                         {
                                    return( token::PARTIAL );
                                }

private                         {
                                    return( token::PRIVATE );
                                }

property                        {
                                    return( token::PROPERTY );
                                }

protected                       {
                                    return( token::PROTECTED );
                                }

public                          {
                                    return( token::PUBLIC );
                                }

readonly                        {
                                    return( token::READONLY );
                                }

ref                             {
                                    return( token::REF );
                                }

remove                          {
                                    return( token::REMOVE );
                                }

return                          {
                                    return( token::RETURN );
                                }

sbyte                           {
                                    return( token::SBYTE );
                                }

sealed                          {
                                    return( token::SEALED );
                                }

select                          {
                                    return( token::SELECT );
                                }

set                             {
                                    return( token::SET );
                                }

short                           {
                                    return( token::SHORT );
                                }

sizeof                          {
                                    return( token::SIZEOF );
                                }

stackalloc                      {
                                    return( token::STACKALLOC );
                                }

static                          {
                                    return( token::STATIC );
                                }

string                          {
                                    return( token::STRING );
                                }

struct                          {
                                    return( token::STRUCT );
                                }

switch                          {
                                    return( token::SWITCH );
                                }

this                            {
                                    return( token::THIS );
                                }

throw                           {
                                    return( token::THROW );
                                }

true                            {
                                    return( token::TRUE );
                                }

try                             {
                                    return( token::TRY );
                                }

type                            {
                                    return( token::TYPE );
                                }

typeof                          {
                                    return( token::TYPEOF );
                                }

uint                            {
                                    return( token::UINT );
                                }

ulong                           {
                                    return( token::ULONG );
                                }

unchecked                       {
                                    return( token::UNCHECKED );
                                }

unsafe                          {
                                    return( token::UNSAFE );
                                }

ushort                          {
                                    return( token::USHORT );
                                }

using                           {
                                    return( token::USING );
                                }

var                             {
                                    return( token::VAR );
                                }

virtual                         {
                                    return( token::VIRTUAL );
                                }

void                            {
                                    return( token::VOID );
                                }

volatile                        {
                                    return( token::VOLATILE );
                                }

when                            {
                                    return( token::WHEN );
                                }

where                           {
                                    return( token::WHERE );
                                }

while                           {
                                    return( token::WHILE );
                                }

yield                           {
                                    return( token::YIELD );
                                }




"@"                             {   /* Operators and punctuators */
                                    return( token::AT );
                                }

"_"                             {
                                    return( token::UNDERSCORE );
                                }

"{"                             {
                                    return( token::LBRACE );
                                }

"}"                             {
                                    return( token::RBRACE );
                                }

"["                             {
                                    return( token::LBRACKET );
                                }

"]"                             {
                                    return( token::RBRACKET );
                                }

"("                             {
                                    return( token::LPAREN );
                                }

")"                             {
                                    return( token::RPAREN );
                                }

"."                             {
                                    return( token::DOT );
                                }

","                             {
                                    return( token::COMMA );
                                }

":"                             {
                                    return( token::COLON );
                                }

";"                             {
                                    return( token::SEMICOLON );
                                }

"+"                             {
                                    return( token::PLUS );
                                }

"-"                             {
                                    return( token::MINUS );
                                }

"*"                             {
                                    return( token::ASTERISK );
                                }

"/"                             {
                                    return( token::SLASH );
                                }

"%"                             {
                                    return( token::PERCENT );
                                }

"&"                             {
                                    return( token::AMPERSAND );
                                }

"|"                             {
                                    return( token::VERTICAL );
                                }

"^"                             {
                                    return( token::CARET );
                                }

"!"                             {
                                    return( token::EXCLAMATION );
                                }

"~"                             {
                                    return( token::TILDE );
                                }

"="                             {
                                    return( token::EQUAL );
                                }

"<"                             {
                                    return( token::LESS );
                                }

">"                             {
                                    return( token::GREATER );
                                }

"?"                             {
                                    return( token::QUESTION );
                                }

"??"                            {
                                    return( token::DBL_QUESTION );
                                }

"::"                            {
                                    return( token::DBL_COLON );
                                }

"++"                            {
                                    return( token::DBL_PLUS );
                                }

"--"                            {
                                    return( token::DBL_MINUS );
                                }

"&&"                            {
                                    return( token::DBL_AMPERSAND );
                                }

"||"                            {
                                    return( token::DBL_VERTICAL );
                                }

"=="                            {
                                    return( token::DBL_EQUAL );
                                }

"!="                            {
                                    return( token::EXCL_EQUAL );
                                }

"<="                            {
                                    return( token::LESS_EQUAL );
                                }

">="                            {
                                    return( token::GREATER_EQUAL );
                                }

"+="                            {
                                    return( token::PLUS_EQUAL );
                                }

"-="                            {
                                    return( token::MINUS_EQUAL );
                                }

"*="                            {
                                    return( token::ASTERISK_EQUAL );
                                }

"/="                            {
                                    return( token::SLASH_EQUAL );
                                }

"%="                            {
                                    return( token::PERCENT_EQUAL );
                                }

"&="                            {
                                    return( token::AMPERSAND_EQUAL );
                                }

"|="                            {
                                    return( token::VERTICAL_EQUAL );
                                }

"^="                            {
                                    return( token::CARET_EQUAL );
                                }

"<<"                            {
                                    return( token::DBL_LESS );
                                }

"<<="                           {
                                    return( token::DBL_LESS_EQUAL );
                                }

">>"                            {
                                    return( token::DBL_GREATER );
                                }

">>="                           {
                                    return( token::DBL_GREATER_EQUAL );
                                }

"=>"                            {
                                    return( token::EQUAL_GREATER );
                                }

"->"                            {
                                    return( token::MINUS_GREATER );
                                }




(\/\/)[^\r\n]*                  {   /* Literals */
                                    yylval->build< std::string >( yytext );
                                    return( token::SINGLE_LINE_COMMENT );
                                }

\/\*(\/|[*]*[^\/*]*)*[*]*\/     {
                                    yylval->build< std::string >( yytext );
                                    return( token::MULTI_LINE_COMMENT );
                                }

@?[_a-zA-Z][_a-zA-Z0-9]*        {
                                    yylval->build< std::string >( yytext );
                                    return( token::IDENTIFIER );
                                }

(((0x|0X)[0-9a-fA-F]+)|([0-9]+))(UL|Ul|uL|ul|LU|Lu|lU|lu|U|u|L|l)? {
                                    yylval->build< std::string >( yytext );
                                    return( token::INTEGER_LITERAL );
                                }

([0-9]+\.[0-9]+([Ee][+-]?[0-9]+)?[FfDdMm]?)|(\.[0-9]+([Ee][+-]?[0-9]+)?[FfDdMm]?)|([0-9]+[Ee][+-]?[0-9]+[FfDdMm]?)|([0-9]+[FfDdMm]) {
                                    yylval->build< std::string >( yytext );
                                    return( token::REAL_LITERAL );
                                }

\'([^\'\\x5c\r\n]|(\\x5c\'|\\x5c\"|\\x5c0|\\x5ca|\\x5cb|\\x5cf|\\x5cn|\\x5cr|\\x5ct|\\x5cv)|\\x5cx[0-9a-fA-F][0-9a-fA-F]?[0-9a-fA-F]?[0-9a-fA-F]?|\\x5c[u][0-9a-fA-F]{4}|\\x5c[U][0-9a-fA-F]{8})\' {
                                    yylval->build< std::string >( yytext );
                                    return( token::CHARACTER_LITERAL );
                                }

(\"([^\"\\x5c\r\n]|(\\x5c\'|\\x5c\"|\\x5c0|\\x5ca|\\x5cb|\\x5cf|\\x5cn|\\x5cr|\\x5ct|\\x5cv)|\\x5cx[0-9a-fA-F][0-9a-fA-F]?[0-9a-fA-F]?[0-9a-fA-F]?|\\x5c[u][0-9a-fA-F]{4}|\\x5c[U][0-9a-fA-F]{8})*\")|(@\"([^\"]|(\"\"))*\") {
                                    yylval->build< std::string >( yytext );
                                    return( token::STRING_LITERAL );
                                }




.*                              ; /* Skip everything else */

%%
