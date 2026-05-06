parser grammar IIC3413DBParser;

options {
    tokenVocab = IIC3413DBLexer;
}

root: query EOF;

query: createQuery | insertQuery | selectQuery;

createQuery: createTable | createIndex;

createTable: CREATE TABLE identifier '(' schema (',' schema)* ')';

createIndex: CREATE INDEX ON table '(' column ')'; // USING method

insertQuery: INSERT INTO identifier VALUES '(' constant (',' constant)* ')';

selectQuery: selectStatement fromStatement whereStatement? limitStatement?;

schema: identifier datatype;

datatype: STR | INT;

selectStatement: SELECT DISTINCT? ('*' | columnList);

columnList: column (',' column)*;

fromStatement: FROM tableList;

tableList: table (',' table)*;

table: identifier (AS identifier)?;

whereStatement: WHERE andExpr;

andExpr: simpleExpr (AND simpleExpr)*;

simpleExpr: comparisonExpr
|           likeExpr
|           betweenExpr
;

comparisonExpr: columnOrConstant (op=('=='|'!='|'<'|'>'|'<='|'>=') columnOrConstant)?;

likeExpr: column LIKE STRING;

betweenExpr: column BETWEEN constant AND constant;

columnOrConstant: column | constant;

column: identifier ('.' identifier)?;

constant: INTEGER | STRING;

identifier: IDENTIFIER | keyword;

limitStatement: LIMIT INTEGER;

keyword: AND
|        AS
|        BETWEEN
|        CREATE
|        DELETE
|        DISTINCT
|        FROM
|				 INDEX
|        INSERT
|        INTO
|        INT
|        LIKE
|        LIMIT
|        OR
|        SELECT
|        SET
|        STR
|        TABLE
|        UPDATE
|        VALUES
|        WHERE
;
