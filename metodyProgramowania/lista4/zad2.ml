module type DICT = sig
  type key      
  type 'a dict  
  val empty : 'a dict 
  val insert : key -> 'a -> 'a dict -> 'a dict    (* klucz, wartość, słownik -> nowy słownik*)
  val remove : key -> 'a dict -> 'a dict          (* klucz, słownik -> nowy słownik*)
  val find_opt : key -> 'a dict -> 'a option      (* klucz, słownik -> wartość option*)
  val find : key -> 'a dict -> 'a                 (* klucz, słownik -> wartość*)
  val to_list : 'a dict -> (key * 'a) list        (* slownik -> lista krotek (klucz,wartość)*)
end

(* 
  module type DICT = sig
  type ('a, 'b) dict
  val empty : ('a, 'b) dict
  val insert : 'a -> 'b -> ('a, 'b) dict -> ('a, 'b) dict
  val remove : 'a -> ('a, 'b) dict -> ('a, 'b) dict
  val find_opt : 'a -> ('a, 'b) dict -> 'b option
  val find : 'a -> ('a, 'b) dict -> 'b
  val to_list : ('a, 'b) dict -> ('a * 'b) list
end   
*)
  