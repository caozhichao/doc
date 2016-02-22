package
{
	import flash.utils.ByteArray;
	import flash.utils.describeType;
	
	import flacc_swig.test.CModule;
	
	/**
	 * flash cc util 
	 * @author caozc
	 * 
	 */	
	public class CCAS3Util
	{
		public function CCAS3Util()
		{
		}
		
		/**
		 * 读取一个c字符串 
		 * 逐个读取直到=0结束
		 * @param ptr 字符串的指针值(首地址值)
		 * @return 
		 * 
		 */		
		public static function readCString(ptr:int):String{
			var bytes:ByteArray = new ByteArray();
			var byte:int = -1;
			var i:int = 0;
			while(byte != 0){
				byte = CModule.read8(ptr + i);
				bytes.writeByte(byte);
				++i;
			}
			return bytes.toString();
		}
		
		/**
		 *  flash as3 静态数据对象转换成对应的cc静态数据对象
		 * @param as3Vo  flash as3  vo
		 * @param cla    要转换的对应的cc 的as3 class类 (cc生成的struct 对应类)
		 * @return       cc vo 对应的指针地址值 
		 * 
		 */		
		public static function as3Vo2CCVo(as3Vo:*,ccAS3Class:Class):int{
			var ptr:int = CModule.malloc(ccAS3Class.size);
			var ccVo:* = new ccAS3Class(CModule.ram,ptr);
			var xml:XML = describeType(as3Vo);//需要优化缓存xml不必每次都解析比较耗性能
			var xmlList:XMLList = xml.child("variable");
			var attributeName:String;
			var attributeType:String;
			for each (var item:XML in xmlList) 
			{
				attributeName = item.attribute("name");
				attributeType = item.attribute("type");
				if(ccVo.hasOwnProperty(attributeName)){
					if(attributeType == "String"){
						var strPtr:int = CModule.mallocString(as3Vo[attributeName]);
						ccVo[attributeName] = strPtr;
					} else {
						ccVo[attributeName] = as3Vo[attributeName];
					}
				}
			}
			return ptr;
		}
		
		/**
		 * 打印一个cc对象 
		 * @param ptr         cc对象的对应的指针值 
		 * @param ccAS3Class  cc对象as3 class 类 (cc生成的对应的struct as3类)
		 * @param as3Class    cc对象对应as3静态数据的as3类(通过该类获取对象有那些字段)
		 * 
		 */		
		public static function traceCCVO(ptr:int,ccAS3Class:Class,as3Class:Class):void{
			var ccVo:* = new ccAS3Class(CModule.ram,ptr);
			var xml:XML = describeType(as3Class);
			var xmlList:XMLList = xml.child("factory")[0].child("variable");
			var attributeName:String;
			var attributeType:String;
			var traceMsg:String = "";
			for each (var item:XML in xmlList) 
			{
				attributeName = item.attribute("name");
				attributeType = item.attribute("type");
				if(ccVo.hasOwnProperty(attributeName)){
					traceMsg += attributeName + ":";
					if(attributeType == "String"){
						var strPtr:int = ccVo[attributeName];
						traceMsg += readCString(strPtr);
					} else {
						traceMsg += ccVo[attributeName];
					}
					traceMsg += "\n";
				}
			}
			trace(traceMsg);
		}
	}
}