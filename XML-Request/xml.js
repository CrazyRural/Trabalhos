var fs = require('fs');
var request = require('request');
var http = require('http');
var xsdval = require('libxmljs');
var xml2js = require('xml2js');
var parser = require('xml2json');
var querystring = require('querystring');
var xslt4node = require('xslt4node');
var DOMParser = require('xmldom').DOMParser;
var parserd = new DOMParser();

var parser = xml2js.Parser();
var xmlj, xsdD, xsd, xml, xml1, xmlD, dom ;

// Vinicius - "http://ruralruby.dlinkddns.com:8011" = Get
// Matheus - "http://tebd.000webhostapp.com" = Get/Post

var urlServerVin = "http://ruralruby.dlinkddns.com:8011";
var urlServerMatA = "http://tebd.000webhostapp.com";

//require('request-debug')(request);
/*
0 - Sucesso
1 - XML inválido
2 - XML mal-formado
3 - Erro Interno
*/

/*
0 - Candidato não encontrado 
1 - Em processamento
2 - Candidato Aprovado e Selecionado
3 - Candidato Aprovado e em Espera
4 - Candidato Não Aprovado
*/

function submeter(xml){
  var form = {
    '': xml.toString(),
  };
  var formData = querystring.stringify(xml);
  var contentLength = formData.length;
  request({
    headers: {
      'Content-Type': 'text/xml'
    },
    uri: urlServerVin,
    body: xml.toString(),
    method: 'POST'
  }, function (err, res, body) {
    if (err) {
      return console.error('Submeter -> Erro', err);
    }
    console.log('Submeter -> sucesso!');
    dom = parserd.parseFromString(body,"text/xml");
    console.log(body);
    parser.parseString(body, function (err, result) {
        xmlr = JSON.stringify(result);
        console.log(result.methodReturn.value[0]);
    });
  });
}

function consultarStatus(xml){
    var form = {
      '': xml.toString(),
    };
    var formData = querystring.stringify(xml);
    var contentLength = formData.length;
    request({
      headers: {
        'Content-Type': 'text/xml'
      },
      uri: urlServerMatA,
      body: xml.toString(),
      method: 'GET'
    }, function (err, res, body) {
      if (err) {
        return console.error('Consultar -> Erro', err);
      }
      console.log('Consultar -> sucesso!');
      dom = parserd.parseFromString(body,"text/xml");
      console.log(body);
      parser.parseString(body, function (err, result) {
          xmlr = JSON.stringify(result);
        console.log(result.methodReturn.value[0]);
      });
    });
}

function main(nomeArquivo, funcao){
    fs.readFile(__dirname+'/xmls/'+ nomeArquivo, 'utf-8', function(err, buf) {
        if(err) { console.log("File not Found!"); return;}
        switch(funcao){
            case 1:
                submeter(buf);
                break;
            case 2:
                consultarStatus(buf);
                break;
        }
        return true;
    });
}
var result = main('consultarStatus1.xml', 2);
var result2 = main('submeter0.xml', 1);

