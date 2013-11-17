// This file is auto-generated header by tools/generate-currency.py.
// So do not edit this file.
#ifndef IV_I18N_CURRENCY_H_
#define IV_I18N_CURRENCY_H_
#include <iv/detail/array.h>
#include <iv/detail/unordered_map.h>
namespace iv {
namespace core {
namespace i18n {

struct CurrencyData {
  static const int kMaxCurrencyCodeSize = 30;
  const char* code;
  const char* name;
  int digits;
  struct CurrencyCode {
    std::size_t size;
    uint16_t data[kMaxCurrencyCodeSize];
  } symbol;

  int CurrencyDigits() const {
    return (digits == -1) ? 2 : digits;
  }
};

typedef std::array<CurrencyData, 271> CurrencyDataArray;
static const CurrencyDataArray kCurrencyData = { {
  { "ADP", "Andorran Peseta", -1, { 0U, {  } } },  // NOLINT
  { "AED", "United Arab Emirates Dirham", 2, { 0U, {  } } },  // NOLINT
  { "AFA", "Afghani (1927-2002)", -1, { 0U, {  } } },  // NOLINT
  { "AFN", "Afghani", 2, { 2U, { 0x41, 0x66 } } },  // NOLINT
  { "ALL", "Albanian Lek", 2, { 3U, { 0x6c, 0x65, 0x6b } } },  // NOLINT
  { "AMD", "Armenian Dram", 2, { 4U, { 0x64, 0x72, 0x61, 0x6d } } },  // NOLINT
  { "ANG", "Netherlands Antillan Guilder", 2, { 5U, { 0x4e, 0x41, 0x20, 0x66, 0x2e } } },  // NOLINT
  { "AOA", "Angolan Kwanza", 2, { 0U, {  } } },  // NOLINT
  { "AOK", "Angolan Kwanza (1977-1990)", -1, { 0U, {  } } },  // NOLINT
  { "AON", "Angolan New Kwanza (1990-2000)", -1, { 0U, {  } } },  // NOLINT
  { "AOR", "Angolan Kwanza Reajustado (1995-1999)", -1, { 0U, {  } } },  // NOLINT
  { "ARA", "Argentine Austral", -1, { 0U, {  } } },  // NOLINT
  { "ARP", "Argentine Peso (1983-1985)", -1, { 0U, {  } } },  // NOLINT
  { "ARS", "Argentine Peso", 2, { 4U, { 0x41, 0x72, 0x67, 0x24 } } },  // NOLINT
  { "ATS", "Austrian Schilling", -1, { 0U, {  } } },  // NOLINT
  { "AUD", "Australian Dollar", 2, { 2U, { 0x24, 0x41 } } },  // NOLINT
  { "AWG", "Aruban Guilder", 2, { 0U, {  } } },  // NOLINT
  { "AZM", "Azerbaijanian Manat (1993-2006)", -1, { 0U, {  } } },  // NOLINT
  { "AZN", "Azerbaijanian Manat", 2, { 0U, {  } } },  // NOLINT
  { "BAD", "Bosnia-Herzegovina Dinar", -1, { 0U, {  } } },  // NOLINT
  { "BAM", "Bosnia-Herzegovina Convertible Mark", 2, { 2U, { 0x4b, 0x4d } } },  // NOLINT
  { "BBD", "Barbados Dollar", 2, { 4U, { 0x42, 0x44, 0x53, 0x24 } } },  // NOLINT
  { "BDT", "Bangladesh Taka", 2, { 2U, { 0x54, 0x6b } } },  // NOLINT
  { "BEC", "Belgian Franc (convertible)", -1, { 0U, {  } } },  // NOLINT
  { "BEF", "Belgian Franc", -1, { 2U, { 0x42, 0x46 } } },  // NOLINT
  { "BEL", "Belgian Franc (financial)", -1, { 0U, {  } } },  // NOLINT
  { "BGL", "Bulgarian Hard Lev", -1, { 3U, { 0x6c, 0x65, 0x76 } } },  // NOLINT
  { "BGN", "Bulgarian New Lev", 2, { 0U, {  } } },  // NOLINT
  { "BHD", "Bahraini Dinar", 3, { 2U, { 0x42, 0x44 } } },  // NOLINT
  { "BIF", "Burundi Franc", 0, { 3U, { 0x46, 0x62, 0x75 } } },  // NOLINT
  { "BMD", "Bermudan Dollar", 2, { 4U, { 0x42, 0x65, 0x72, 0x24 } } },  // NOLINT
  { "BND", "Brunei Dollar", 2, { 0U, {  } } },  // NOLINT
  { "BOB", "Boliviano", 2, { 2U, { 0x42, 0x73 } } },  // NOLINT
  { "BOP", "Bolivian Peso", -1, { 0U, {  } } },  // NOLINT
  { "BOV", "Bolivian Mvdol", 2, { 0U, {  } } },  // NOLINT
  { "BRB", "Brazilian Cruzeiro Novo (1967-1986)", -1, { 0U, {  } } },  // NOLINT
  { "BRC", "Brazilian Cruzado", -1, { 0U, {  } } },  // NOLINT
  { "BRE", "Brazilian Cruzeiro (1990-1993)", -1, { 0U, {  } } },  // NOLINT
  { "BRL", "Brazilian Real", 2, { 0U, {  } } },  // NOLINT
  { "BRN", "Brazilian Cruzado Novo", -1, { 0U, {  } } },  // NOLINT
  { "BRR", "Brazilian Cruzeiro", -1, { 0U, {  } } },  // NOLINT
  { "BSD", "Bahamian Dollar", 2, { 0U, {  } } },  // NOLINT
  { "BTN", "Bhutan Ngultrum", 2, { 2U, { 0x4e, 0x75 } } },  // NOLINT
  { "BUK", "Burmese Kyat", -1, { 0U, {  } } },  // NOLINT
  { "BWP", "Botswanan Pula", 2, { 0U, {  } } },  // NOLINT
  { "BYB", "Belarussian New Ruble (1994-1999)", -1, { 0U, {  } } },  // NOLINT
  { "BYR", "Belarussian Ruble", 0, { 3U, { 0x52, 0x62, 0x6c } } },  // NOLINT
  { "BZD", "Belize Dollar", 2, { 3U, { 0x42, 0x5a, 0x24 } } },  // NOLINT
  { "CAD", "Canadian Dollar", 2, { 4U, { 0x43, 0x61, 0x6e, 0x24 } } },  // NOLINT
  { "CDF", "Congolese Franc Congolais", 2, { 0U, {  } } },  // NOLINT
  { "CHE", "WIR Euro", 2, { 0U, {  } } },  // NOLINT
  { "CHF", "Swiss Franc", 2, { 3U, { 0x53, 0x77, 0x46 } } },  // NOLINT
  { "CHW", "WIR Franc", 2, { 0U, {  } } },  // NOLINT
  { "CLF", "Chilean Unidades de Fomento", 0, { 0U, {  } } },  // NOLINT
  { "CLP", "Chilean Peso", 0, { 3U, { 0x43, 0x68, 0x24 } } },  // NOLINT
  { "CNY", "Chinese Yuan Renminbi", 2, { 1U, { 0x59 } } },  // NOLINT
  { "COP", "Colombian Peso", 2, { 4U, { 0x43, 0x6f, 0x6c, 0x24 } } },  // NOLINT
  { "COU", "Unidad de Valor Real", 2, { 0U, {  } } },  // NOLINT
  { "CRC", "Costa Rican Colon", 2, { 1U, { 0x43 } } },  // NOLINT
  { "CSD", "Old Serbian Dinar", -1, { 0U, {  } } },  // NOLINT
  { "CSK", "Czechoslovak Hard Koruna", -1, { 0U, {  } } },  // NOLINT
  { "CUP", "Cuban Peso", 2, { 0U, {  } } },  // NOLINT
  { "CVE", "Cape Verde Escudo", 2, { 5U, { 0x43, 0x56, 0x45, 0x73, 0x63 } } },  // NOLINT
  { "CYP", "Cyprus Pound", -1, { 2U, { 0xa3, 0x43 } } },  // NOLINT
  { "CZK", "Czech Republic Koruna", 2, { 0U, {  } } },  // NOLINT
  { "DDM", "East German Ostmark", -1, { 0U, {  } } },  // NOLINT
  { "DEM", "Deutsche Mark", -1, { 0U, {  } } },  // NOLINT
  { "DJF", "Djibouti Franc", 0, { 2U, { 0x44, 0x46 } } },  // NOLINT
  { "DKK", "Danish Krone", 2, { 3U, { 0x44, 0x4b, 0x72 } } },  // NOLINT
  { "DOP", "Dominican Peso", 2, { 3U, { 0x52, 0x44, 0x24 } } },  // NOLINT
  { "DZD", "Algerian Dinar", 2, { 2U, { 0x44, 0x41 } } },  // NOLINT
  { "ECS", "Ecuador Sucre", -1, { 0U, {  } } },  // NOLINT
  { "ECV", "Ecuador Unidad de Valor Constante (UVC)", -1, { 0U, {  } } },  // NOLINT
  { "EEK", "Estonian Kroon", -1, { 0U, {  } } },  // NOLINT
  { "EGP", "Egyptian Pound", 2, { 0U, {  } } },  // NOLINT
  { "EQE", "Ekwele", -1, { 0U, {  } } },  // NOLINT
  { "ERN", "Eritrean Nakfa", 2, { 0U, {  } } },  // NOLINT
  { "ESA", "Spanish Peseta (A account)", -1, { 0U, {  } } },  // NOLINT
  { "ESB", "Spanish Peseta (convertible account)", -1, { 0U, {  } } },  // NOLINT
  { "ESP", "Spanish Peseta", -1, { 1U, { 0x20a7 } } },  // NOLINT
  { "ETB", "Ethiopian Birr", 2, { 2U, { 0x42, 0x72 } } },  // NOLINT
  { "EUR", "Euro", 2, { 0U, {  } } },  // NOLINT
  { "FIM", "Finnish Markka", -1, { 0U, {  } } },  // NOLINT
  { "FJD", "Fiji Dollar", 2, { 2U, { 0x46, 0x24 } } },  // NOLINT
  { "FKP", "Falkland Islands Pound", 2, { 0U, {  } } },  // NOLINT
  { "FRF", "French Franc", -1, { 0U, {  } } },  // NOLINT
  { "GBP", "British Pound Sterling", 2, { 1U, { 0xa3 } } },  // NOLINT
  { "GEK", "Georgian Kupon Larit", -1, { 0U, {  } } },  // NOLINT
  { "GEL", "Georgian Lari", 2, { 4U, { 0x6c, 0x61, 0x72, 0x69 } } },  // NOLINT
  { "GHC", "Ghana Cedi (1979-2007)", -1, { 0U, {  } } },  // NOLINT
  { "GHS", "Ghana Cedi", 2, { 3U, { 0x47, 0x48, 0xa2 } } },  // NOLINT
  { "GIP", "Gibraltar Pound", 2, { 0U, {  } } },  // NOLINT
  { "GMD", "Gambia Dalasi", 2, { 0U, {  } } },  // NOLINT
  { "GNF", "Guinea Franc", 0, { 2U, { 0x47, 0x46 } } },  // NOLINT
  { "GNS", "Guinea Syli", -1, { 0U, {  } } },  // NOLINT
  { "GQE", "Equatorial Guinea Ekwele Guineana", -1, { 0U, {  } } },  // NOLINT
  { "GRD", "Greek Drachma", -1, { 0U, {  } } },  // NOLINT
  { "GTQ", "Guatemala Quetzal", 2, { 1U, { 0x51 } } },  // NOLINT
  { "GWE", "Portuguese Guinea Escudo", -1, { 0U, {  } } },  // NOLINT
  { "GWP", "Guinea-Bissau Peso", -1, { 0U, {  } } },  // NOLINT
  { "GYD", "Guyana Dollar", 2, { 2U, { 0x47, 0x24 } } },  // NOLINT
  { "HKD", "Hong Kong Dollar", 2, { 3U, { 0x48, 0x4b, 0x24 } } },  // NOLINT
  { "HNL", "Honduras Lempira", 2, { 1U, { 0x4c } } },  // NOLINT
  { "HRD", "Croatian Dinar", -1, { 0U, {  } } },  // NOLINT
  { "HRK", "Croatian Kuna", 2, { 0U, {  } } },  // NOLINT
  { "HTG", "Haitian Gourde", 2, { 0U, {  } } },  // NOLINT
  { "HUF", "Hungarian Forint", 2, { 2U, { 0x46, 0x74 } } },  // NOLINT
  { "IDR", "Indonesian Rupiah", 2, { 2U, { 0x52, 0x70 } } },  // NOLINT
  { "IEP", "Irish Pound", -1, { 3U, { 0x49, 0x52, 0xa3 } } },  // NOLINT
  { "ILP", "Israeli Pound", -1, { 0U, {  } } },  // NOLINT
  { "ILS", "Israeli New Sheqel", 2, { 0U, {  } } },  // NOLINT
  { "INR", "Indian Rupee", 2, { 0U, {  } } },  // NOLINT
  { "IQD", "Iraqi Dinar", 3, { 2U, { 0x49, 0x44 } } },  // NOLINT
  { "IRR", "Iranian Rial", 2, { 2U, { 0x52, 0x49 } } },  // NOLINT
  { "ISK", "Icelandic Krona", 0, { 0U, {  } } },  // NOLINT
  { "ITL", "Italian Lira", -1, { 1U, { 0x20a4 } } },  // NOLINT
  { "JMD", "Jamaican Dollar", 2, { 2U, { 0x4a, 0x24 } } },  // NOLINT
  { "JOD", "Jordanian Dinar", 3, { 2U, { 0x4a, 0x44 } } },  // NOLINT
  { "JPY", "Japanese Yen", 0, { 1U, { 0xa5 } } },  // NOLINT
  { "KES", "Kenyan Shilling", 2, { 4U, { 0x4b, 0x20, 0x53, 0x68 } } },  // NOLINT
  { "KGS", "Kyrgystan Som", 2, { 3U, { 0x73, 0x6f, 0x6d } } },  // NOLINT
  { "KHR", "Cambodian Riel", 2, { 2U, { 0x43, 0x52 } } },  // NOLINT
  { "KMF", "Comoro Franc", 0, { 2U, { 0x43, 0x46 } } },  // NOLINT
  { "KPW", "North Korean Won", 2, { 0U, {  } } },  // NOLINT
  { "KRW", "South Korean Won", 0, { 0U, {  } } },  // NOLINT
  { "KWD", "Kuwaiti Dinar", 3, { 2U, { 0x4b, 0x44 } } },  // NOLINT
  { "KYD", "Cayman Islands Dollar", 2, { 0U, {  } } },  // NOLINT
  { "KZT", "Kazakhstan Tenge", 2, { 1U, { 0x54 } } },  // NOLINT
  { "LAK", "Laotian Kip", 2, { 0U, {  } } },  // NOLINT
  { "LBP", "Lebanese Pound", 2, { 2U, { 0x4c, 0x4c } } },  // NOLINT
  { "LKR", "Sri Lanka Rupee", 2, { 5U, { 0x53, 0x4c, 0x20, 0x52, 0x65 } } },  // NOLINT
  { "LRD", "Liberian Dollar", 2, { 0U, {  } } },  // NOLINT
  { "LSL", "Lesotho Loti", 2, { 1U, { 0x4d } } },  // NOLINT
  { "LSM", "Maloti", -1, { 0U, {  } } },  // NOLINT
  { "LTL", "Lithuanian Lita", 2, { 0U, {  } } },  // NOLINT
  { "LTT", "Lithuanian Talonas", -1, { 0U, {  } } },  // NOLINT
  { "LUC", "Luxembourg Convertible Franc", -1, { 0U, {  } } },  // NOLINT
  { "LUF", "Luxembourg Franc", -1, { 0U, {  } } },  // NOLINT
  { "LUL", "Luxembourg Financial Franc", -1, { 0U, {  } } },  // NOLINT
  { "LVL", "Latvian Lats", 2, { 0U, {  } } },  // NOLINT
  { "LVR", "Latvian Ruble", -1, { 0U, {  } } },  // NOLINT
  { "LYD", "Libyan Dinar", 3, { 2U, { 0x4c, 0x44 } } },  // NOLINT
  { "MAD", "Moroccan Dirham", 2, { 0U, {  } } },  // NOLINT
  { "MAF", "Moroccan Franc", -1, { 0U, {  } } },  // NOLINT
  { "MDL", "Moldovan Leu", 2, { 0U, {  } } },  // NOLINT
  { "MGA", "Madagascar Ariary", 2, { 0U, {  } } },  // NOLINT
  { "MGF", "Madagascar Franc", -1, { 0U, {  } } },  // NOLINT
  { "MKD", "Macedonian Denar", 2, { 4U, { 0x4d, 0x44, 0x65, 0x6e } } },  // NOLINT
  { "MLF", "Mali Franc", -1, { 0U, {  } } },  // NOLINT
  { "MMK", "Myanmar Kyat", 2, { 0U, {  } } },  // NOLINT
  { "MNT", "Mongolian Tugrik", 2, { 3U, { 0x54, 0x75, 0x67 } } },  // NOLINT
  { "MOP", "Macao Pataca", 2, { 0U, {  } } },  // NOLINT
  { "MRO", "Mauritania Ouguiya", 2, { 2U, { 0x55, 0x4d } } },  // NOLINT
  { "MTL", "Maltese Lira", -1, { 2U, { 0x4c, 0x6d } } },  // NOLINT
  { "MTP", "Maltese Pound", -1, { 0U, {  } } },  // NOLINT
  { "MUR", "Mauritius Rupee", 2, { 0U, {  } } },  // NOLINT
  { "MVR", "Maldive Islands Rufiyaa", 2, { 0U, {  } } },  // NOLINT
  { "MWK", "Malawi Kwacha", 2, { 2U, { 0x4d, 0x4b } } },  // NOLINT
  { "MXN", "Mexican Peso", 2, { 4U, { 0x4d, 0x45, 0x58, 0x24 } } },  // NOLINT
  { "MXP", "Mexican Silver Peso (1861-1992)", -1, { 0U, {  } } },  // NOLINT
  { "MXV", "Mexican Unidad de Inversion (UDI)", 2, { 0U, {  } } },  // NOLINT
  { "MYR", "Malaysian Ringgit", 2, { 2U, { 0x52, 0x4d } } },  // NOLINT
  { "MZE", "Mozambique Escudo", -1, { 0U, {  } } },  // NOLINT
  { "MZM", "Old Mozambique Metical", -1, { 2U, { 0x4d, 0x74 } } },  // NOLINT
  { "MZN", "Mozambique Metical", 2, { 3U, { 0x4d, 0x54, 0x6e } } },  // NOLINT
  { "NAD", "Namibia Dollar", 2, { 2U, { 0x4e, 0x24 } } },  // NOLINT
  { "NGN", "Nigerian Naira", 2, { 0U, {  } } },  // NOLINT
  { "NIC", "Nicaraguan Cordoba", -1, { 0U, {  } } },  // NOLINT
  { "NIO", "Nicaraguan Cordoba Oro", 2, { 0U, {  } } },  // NOLINT
  { "NLG", "Netherlands Guilder", -1, { 0U, {  } } },  // NOLINT
  { "NOK", "Norwegian Krone", 2, { 3U, { 0x4e, 0x4b, 0x72 } } },  // NOLINT
  { "NPR", "Nepalese Rupee", 2, { 3U, { 0x4e, 0x72, 0x73 } } },  // NOLINT
  { "NZD", "New Zealand Dollar", 2, { 3U, { 0x24, 0x4e, 0x5a } } },  // NOLINT
  { "OMR", "Oman Rial", 3, { 2U, { 0x52, 0x4f } } },  // NOLINT
  { "PAB", "Panamanian Balboa", 2, { 0U, {  } } },  // NOLINT
  { "PEI", "Peruvian Inti", -1, { 0U, {  } } },  // NOLINT
  { "PEN", "Peruvian Sol Nuevo", 2, { 0U, {  } } },  // NOLINT
  { "PES", "Peruvian Sol", -1, { 0U, {  } } },  // NOLINT
  { "PGK", "Papua New Guinea Kina", 2, { 0U, {  } } },  // NOLINT
  { "PHP", "Philippine Peso", 2, { 3U, { 0x50, 0x68, 0x70 } } },  // NOLINT
  { "PKR", "Pakistan Rupee", 2, { 3U, { 0x50, 0x72, 0x61 } } },  // NOLINT
  { "PLN", "Polish Zloty", 2, { 2U, { 0x5a, 0x6c } } },  // NOLINT
  { "PLZ", "Polish Zloty (1950-1995)", -1, { 0U, {  } } },  // NOLINT
  { "PTE", "Portuguese Escudo", -1, { 0U, {  } } },  // NOLINT
  { "PYG", "Paraguay Guarani", 0, { 0U, {  } } },  // NOLINT
  { "QAR", "Qatari Rial", 2, { 2U, { 0x51, 0x52 } } },  // NOLINT
  { "RHD", "Rhodesian Dollar", -1, { 0U, {  } } },  // NOLINT
  { "ROL", "Old Romanian Leu", -1, { 30U, { 0x3d, 0x30, 0x23, 0x4f, 0x6c, 0x64, 0x20, 0x6c, 0x65, 0x69, 0x7c, 0x31, 0x23, 0x4f, 0x6c, 0x64, 0x20, 0x6c, 0x65, 0x75, 0x7c, 0x31, 0x3c, 0x4f, 0x6c, 0x64, 0x20, 0x6c, 0x65, 0x69 } } },  // NOLINT
  { "RON", "Romanian Leu", 2, { 18U, { 0x3d, 0x30, 0x23, 0x6c, 0x65, 0x69, 0x7c, 0x31, 0x23, 0x6c, 0x65, 0x75, 0x7c, 0x31, 0x3c, 0x6c, 0x65, 0x69 } } },  // NOLINT
  { "RSD", "Serbian Dinar", 2, { 0U, {  } } },  // NOLINT
  { "RUB", "Russian Ruble", 2, { 0U, {  } } },  // NOLINT
  { "RUR", "Russian Ruble (1991-1998)", -1, { 0U, {  } } },  // NOLINT
  { "RWF", "Rwandan Franc", 0, { 0U, {  } } },  // NOLINT
  { "SAR", "Saudi Riyal", 2, { 3U, { 0x53, 0x52, 0x6c } } },  // NOLINT
  { "SBD", "Solomon Islands Dollar", 2, { 3U, { 0x53, 0x49, 0x24 } } },  // NOLINT
  { "SCR", "Seychelles Rupee", 2, { 2U, { 0x53, 0x52 } } },  // NOLINT
  { "SDD", "Old Sudanese Dinar", -1, { 0U, {  } } },  // NOLINT
  { "SDG", "Sudanese Pound", 2, { 0U, {  } } },  // NOLINT
  { "SDP", "Old Sudanese Pound", -1, { 0U, {  } } },  // NOLINT
  { "SEK", "Swedish Krona", 2, { 3U, { 0x53, 0x4b, 0x72 } } },  // NOLINT
  { "SGD", "Singapore Dollar", 2, { 2U, { 0x53, 0x24 } } },  // NOLINT
  { "SHP", "Saint Helena Pound", 2, { 0U, {  } } },  // NOLINT
  { "SIT", "Slovenia Tolar", -1, { 0U, {  } } },  // NOLINT
  { "SKK", "Slovak Koruna", -1, { 2U, { 0x53, 0x6b } } },  // NOLINT
  { "SLL", "Sierra Leone Leone", 2, { 0U, {  } } },  // NOLINT
  { "SOS", "Somali Shilling", 2, { 7U, { 0x53, 0x6f, 0x2e, 0x20, 0x53, 0x68, 0x2e } } },  // NOLINT
  { "SRD", "Surinam Dollar", 2, { 0U, {  } } },  // NOLINT
  { "SRG", "Suriname Guilder", -1, { 2U, { 0x53, 0x66 } } },  // NOLINT
  { "STD", "Sao Tome and Principe Dobra", 2, { 2U, { 0x44, 0x62 } } },  // NOLINT
  { "SUR", "Soviet Rouble", -1, { 0U, {  } } },  // NOLINT
  { "SVC", "El Salvador Colon", 2, { 0U, {  } } },  // NOLINT
  { "SYP", "Syrian Pound", 2, { 2U, { 0x4c, 0x53 } } },  // NOLINT
  { "SZL", "Swaziland Lilangeni", 2, { 1U, { 0x45 } } },  // NOLINT
  { "THB", "Thai Baht", 2, { 0U, {  } } },  // NOLINT
  { "TJR", "Tajikistan Ruble", -1, { 0U, {  } } },  // NOLINT
  { "TJS", "Tajikistan Somoni", 2, { 0U, {  } } },  // NOLINT
  { "TMM", "Turkmenistan Manat", -1, { 0U, {  } } },  // NOLINT
  { "TND", "Tunisian Dinar", 3, { 0U, {  } } },  // NOLINT
  { "TOP", "Tonga Paʻanga", 2, { 2U, { 0x54, 0x24 } } },  // NOLINT
  { "TPE", "Timor Escudo", -1, { 0U, {  } } },  // NOLINT
  { "TRL", "Turkish Lira", -1, { 2U, { 0x54, 0x4c } } },  // NOLINT
  { "TRY", "New Turkish Lira", 2, { 0U, {  } } },  // NOLINT
  { "TTD", "Trinidad and Tobago Dollar", 2, { 3U, { 0x54, 0x54, 0x24 } } },  // NOLINT
  { "TWD", "Taiwan New Dollar", 2, { 3U, { 0x4e, 0x54, 0x24 } } },  // NOLINT
  { "TZS", "Tanzanian Shilling", 2, { 4U, { 0x54, 0x20, 0x53, 0x68 } } },  // NOLINT
  { "UAH", "Ukrainian Hryvnia", 2, { 0U, {  } } },  // NOLINT
  { "UAK", "Ukrainian Karbovanetz", -1, { 0U, {  } } },  // NOLINT
  { "UGS", "Ugandan Shilling (1966-1987)", -1, { 0U, {  } } },  // NOLINT
  { "UGX", "Ugandan Shilling", 2, { 4U, { 0x55, 0x20, 0x53, 0x68 } } },  // NOLINT
  { "USD", "US Dollar", 2, { 1U, { 0x24 } } },  // NOLINT
  { "USN", "US Dollar (Next day)", 2, { 0U, {  } } },  // NOLINT
  { "USS", "US Dollar (Same day)", 2, { 0U, {  } } },  // NOLINT
  { "UYI", "Uruguay Peso en Unidades Indexadas", 0, { 0U, {  } } },  // NOLINT
  { "UYP", "Uruguay Peso (1975-1993)", -1, { 0U, {  } } },  // NOLINT
  { "UYU", "Uruguay Peso Uruguayo", 2, { 3U, { 0x55, 0x72, 0x24 } } },  // NOLINT
  { "UZS", "Uzbekistan Sum", 2, { 0U, {  } } },  // NOLINT
  { "VEB", "Venezuelan Bolivar", -1, { 2U, { 0x42, 0x65 } } },  // NOLINT
  { "VEF", "Venezuelan Bolivar Fuerte", 2, { 3U, { 0x42, 0x73, 0x46 } } },  // NOLINT
  { "VND", "Vietnamese Dong", 0, { 0U, {  } } },  // NOLINT
  { "VUV", "Vanuatu Vatu", 0, { 2U, { 0x56, 0x54 } } },  // NOLINT
  { "WST", "Western Samoa Tala", 2, { 0U, {  } } },  // NOLINT
  { "XAF", "CFA Franc BEAC", 0, { 0U, {  } } },  // NOLINT
  { "XAG", "Silver", -1, { 0U, {  } } },  // NOLINT
  { "XAU", "Gold", -1, { 0U, {  } } },  // NOLINT
  { "XBA", "European Composite Unit", -1, { 0U, {  } } },  // NOLINT
  { "XBB", "European Monetary Unit", -1, { 0U, {  } } },  // NOLINT
  { "XBC", "European Unit of Account (XBC)", -1, { 0U, {  } } },  // NOLINT
  { "XBD", "European Unit of Account (XBD)", -1, { 0U, {  } } },  // NOLINT
  { "XCD", "East Caribbean Dollar", 2, { 3U, { 0x45, 0x43, 0x24 } } },  // NOLINT
  { "XDR", "Special Drawing Rights", -1, { 0U, {  } } },  // NOLINT
  { "XEU", "European Currency Unit", -1, { 0U, {  } } },  // NOLINT
  { "XFO", "French Gold Franc", -1, { 0U, {  } } },  // NOLINT
  { "XFU", "French UIC-Franc", -1, { 0U, {  } } },  // NOLINT
  { "XOF", "CFA Franc BCEAO", 0, { 0U, {  } } },  // NOLINT
  { "XPD", "Palladium", -1, { 0U, {  } } },  // NOLINT
  { "XPF", "CFP Franc", 0, { 4U, { 0x43, 0x46, 0x50, 0x46 } } },  // NOLINT
  { "XPT", "Platinum", -1, { 0U, {  } } },  // NOLINT
  { "XRE", "RINET Funds", -1, { 0U, {  } } },  // NOLINT
  { "XTS", "Testing Currency Code", -1, { 0U, {  } } },  // NOLINT
  { "XXX", "Unknown or Invalid Currency", -1, { 0U, {  } } },  // NOLINT
  { "YDD", "Yemeni Dinar", -1, { 0U, {  } } },  // NOLINT
  { "YER", "Yemeni Rial", 2, { 3U, { 0x59, 0x52, 0x6c } } },  // NOLINT
  { "YUD", "Yugoslavian Hard Dinar", -1, { 0U, {  } } },  // NOLINT
  { "YUM", "Yugoslavian Noviy Dinar", -1, { 0U, {  } } },  // NOLINT
  { "YUN", "Yugoslavian Convertible Dinar", -1, { 0U, {  } } },  // NOLINT
  { "ZAL", "South African Rand (financial)", -1, { 0U, {  } } },  // NOLINT
  { "ZAR", "South African Rand", 2, { 1U, { 0x52 } } },  // NOLINT
  { "ZMK", "Zambian Kwacha", 2, { 0U, {  } } },  // NOLINT
  { "ZRN", "Zairean New Zaire", -1, { 0U, {  } } },  // NOLINT
  { "ZRZ", "Zairean Zaire", -1, { 0U, {  } } },  // NOLINT
  { "ZWD", "Zimbabwe Dollar", -1, { 2U, { 0x5a, 0x24 } } }  // NOLINT
} };

class Currency {
 public:
  enum Type {
    CURRENCY_ADP,
    CURRENCY_AED,
    CURRENCY_AFA,
    CURRENCY_AFN,
    CURRENCY_ALL,
    CURRENCY_AMD,
    CURRENCY_ANG,
    CURRENCY_AOA,
    CURRENCY_AOK,
    CURRENCY_AON,
    CURRENCY_AOR,
    CURRENCY_ARA,
    CURRENCY_ARP,
    CURRENCY_ARS,
    CURRENCY_ATS,
    CURRENCY_AUD,
    CURRENCY_AWG,
    CURRENCY_AZM,
    CURRENCY_AZN,
    CURRENCY_BAD,
    CURRENCY_BAM,
    CURRENCY_BBD,
    CURRENCY_BDT,
    CURRENCY_BEC,
    CURRENCY_BEF,
    CURRENCY_BEL,
    CURRENCY_BGL,
    CURRENCY_BGN,
    CURRENCY_BHD,
    CURRENCY_BIF,
    CURRENCY_BMD,
    CURRENCY_BND,
    CURRENCY_BOB,
    CURRENCY_BOP,
    CURRENCY_BOV,
    CURRENCY_BRB,
    CURRENCY_BRC,
    CURRENCY_BRE,
    CURRENCY_BRL,
    CURRENCY_BRN,
    CURRENCY_BRR,
    CURRENCY_BSD,
    CURRENCY_BTN,
    CURRENCY_BUK,
    CURRENCY_BWP,
    CURRENCY_BYB,
    CURRENCY_BYR,
    CURRENCY_BZD,
    CURRENCY_CAD,
    CURRENCY_CDF,
    CURRENCY_CHE,
    CURRENCY_CHF,
    CURRENCY_CHW,
    CURRENCY_CLF,
    CURRENCY_CLP,
    CURRENCY_CNY,
    CURRENCY_COP,
    CURRENCY_COU,
    CURRENCY_CRC,
    CURRENCY_CSD,
    CURRENCY_CSK,
    CURRENCY_CUP,
    CURRENCY_CVE,
    CURRENCY_CYP,
    CURRENCY_CZK,
    CURRENCY_DDM,
    CURRENCY_DEM,
    CURRENCY_DJF,
    CURRENCY_DKK,
    CURRENCY_DOP,
    CURRENCY_DZD,
    CURRENCY_ECS,
    CURRENCY_ECV,
    CURRENCY_EEK,
    CURRENCY_EGP,
    CURRENCY_EQE,
    CURRENCY_ERN,
    CURRENCY_ESA,
    CURRENCY_ESB,
    CURRENCY_ESP,
    CURRENCY_ETB,
    CURRENCY_EUR,
    CURRENCY_FIM,
    CURRENCY_FJD,
    CURRENCY_FKP,
    CURRENCY_FRF,
    CURRENCY_GBP,
    CURRENCY_GEK,
    CURRENCY_GEL,
    CURRENCY_GHC,
    CURRENCY_GHS,
    CURRENCY_GIP,
    CURRENCY_GMD,
    CURRENCY_GNF,
    CURRENCY_GNS,
    CURRENCY_GQE,
    CURRENCY_GRD,
    CURRENCY_GTQ,
    CURRENCY_GWE,
    CURRENCY_GWP,
    CURRENCY_GYD,
    CURRENCY_HKD,
    CURRENCY_HNL,
    CURRENCY_HRD,
    CURRENCY_HRK,
    CURRENCY_HTG,
    CURRENCY_HUF,
    CURRENCY_IDR,
    CURRENCY_IEP,
    CURRENCY_ILP,
    CURRENCY_ILS,
    CURRENCY_INR,
    CURRENCY_IQD,
    CURRENCY_IRR,
    CURRENCY_ISK,
    CURRENCY_ITL,
    CURRENCY_JMD,
    CURRENCY_JOD,
    CURRENCY_JPY,
    CURRENCY_KES,
    CURRENCY_KGS,
    CURRENCY_KHR,
    CURRENCY_KMF,
    CURRENCY_KPW,
    CURRENCY_KRW,
    CURRENCY_KWD,
    CURRENCY_KYD,
    CURRENCY_KZT,
    CURRENCY_LAK,
    CURRENCY_LBP,
    CURRENCY_LKR,
    CURRENCY_LRD,
    CURRENCY_LSL,
    CURRENCY_LSM,
    CURRENCY_LTL,
    CURRENCY_LTT,
    CURRENCY_LUC,
    CURRENCY_LUF,
    CURRENCY_LUL,
    CURRENCY_LVL,
    CURRENCY_LVR,
    CURRENCY_LYD,
    CURRENCY_MAD,
    CURRENCY_MAF,
    CURRENCY_MDL,
    CURRENCY_MGA,
    CURRENCY_MGF,
    CURRENCY_MKD,
    CURRENCY_MLF,
    CURRENCY_MMK,
    CURRENCY_MNT,
    CURRENCY_MOP,
    CURRENCY_MRO,
    CURRENCY_MTL,
    CURRENCY_MTP,
    CURRENCY_MUR,
    CURRENCY_MVR,
    CURRENCY_MWK,
    CURRENCY_MXN,
    CURRENCY_MXP,
    CURRENCY_MXV,
    CURRENCY_MYR,
    CURRENCY_MZE,
    CURRENCY_MZM,
    CURRENCY_MZN,
    CURRENCY_NAD,
    CURRENCY_NGN,
    CURRENCY_NIC,
    CURRENCY_NIO,
    CURRENCY_NLG,
    CURRENCY_NOK,
    CURRENCY_NPR,
    CURRENCY_NZD,
    CURRENCY_OMR,
    CURRENCY_PAB,
    CURRENCY_PEI,
    CURRENCY_PEN,
    CURRENCY_PES,
    CURRENCY_PGK,
    CURRENCY_PHP,
    CURRENCY_PKR,
    CURRENCY_PLN,
    CURRENCY_PLZ,
    CURRENCY_PTE,
    CURRENCY_PYG,
    CURRENCY_QAR,
    CURRENCY_RHD,
    CURRENCY_ROL,
    CURRENCY_RON,
    CURRENCY_RSD,
    CURRENCY_RUB,
    CURRENCY_RUR,
    CURRENCY_RWF,
    CURRENCY_SAR,
    CURRENCY_SBD,
    CURRENCY_SCR,
    CURRENCY_SDD,
    CURRENCY_SDG,
    CURRENCY_SDP,
    CURRENCY_SEK,
    CURRENCY_SGD,
    CURRENCY_SHP,
    CURRENCY_SIT,
    CURRENCY_SKK,
    CURRENCY_SLL,
    CURRENCY_SOS,
    CURRENCY_SRD,
    CURRENCY_SRG,
    CURRENCY_STD,
    CURRENCY_SUR,
    CURRENCY_SVC,
    CURRENCY_SYP,
    CURRENCY_SZL,
    CURRENCY_THB,
    CURRENCY_TJR,
    CURRENCY_TJS,
    CURRENCY_TMM,
    CURRENCY_TND,
    CURRENCY_TOP,
    CURRENCY_TPE,
    CURRENCY_TRL,
    CURRENCY_TRY,
    CURRENCY_TTD,
    CURRENCY_TWD,
    CURRENCY_TZS,
    CURRENCY_UAH,
    CURRENCY_UAK,
    CURRENCY_UGS,
    CURRENCY_UGX,
    CURRENCY_USD,
    CURRENCY_USN,
    CURRENCY_USS,
    CURRENCY_UYI,
    CURRENCY_UYP,
    CURRENCY_UYU,
    CURRENCY_UZS,
    CURRENCY_VEB,
    CURRENCY_VEF,
    CURRENCY_VND,
    CURRENCY_VUV,
    CURRENCY_WST,
    CURRENCY_XAF,
    CURRENCY_XAG,
    CURRENCY_XAU,
    CURRENCY_XBA,
    CURRENCY_XBB,
    CURRENCY_XBC,
    CURRENCY_XBD,
    CURRENCY_XCD,
    CURRENCY_XDR,
    CURRENCY_XEU,
    CURRENCY_XFO,
    CURRENCY_XFU,
    CURRENCY_XOF,
    CURRENCY_XPD,
    CURRENCY_XPF,
    CURRENCY_XPT,
    CURRENCY_XRE,
    CURRENCY_XTS,
    CURRENCY_XXX,
    CURRENCY_YDD,
    CURRENCY_YER,
    CURRENCY_YUD,
    CURRENCY_YUM,
    CURRENCY_YUN,
    CURRENCY_ZAL,
    CURRENCY_ZAR,
    CURRENCY_ZMK,
    CURRENCY_ZRN,
    CURRENCY_ZRZ,
    CURRENCY_ZWD,
    NUM_OF_CURRENCIES
  };

  enum Display {
    CODE,
    SYMBOL,
    NAME
  };

  typedef CurrencyData Data;
  typedef std::unordered_map<std::string, const Data*> CurrencyMap;

  static const Data* Lookup(StringPiece name) {
    const CurrencyMap::const_iterator it = Map().find(name);
    if (it != Map().end()) {
      return it->second;
    }
    return nullptr;
  }

  static const Data* Lookup(Type type) {
    assert(type < NUM_OF_CURRENCIES);
    return kCurrencyData.data() + type;
  }

 private:
  static const CurrencyMap& Map() {
    static const CurrencyMap map = InitMap();
    return map;
  }

  static CurrencyMap InitMap() {
    CurrencyMap map;
    for (const Data* it = kCurrencyData.data(),  // NOLINT
         *last = kCurrencyData.data() + kCurrencyData.size();
         it != last; ++it) {
      map.insert(std::make_pair(it->code, it));
    }
    return map;
  }
};

} } }  // namespace iv::core::i18n
#endif  // IV_I18N_CURRENCY_H_
