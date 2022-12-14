<?php

	namespace Proj\Admin\Units;

	use Base\Units;
	use Base\Instance;
	use Base\DB\TableMySQLi;
	use Proj\Units\Consts;
	use Proj\DB;

	require DIR_UNITS . 'catalogs/consts.inc';

	class Catalogs extends Units implements Consts\Catalogs {
		use Instance;

		private DB $db;

		private function __construct() {
			parent::__construct(self::ID, self::NAME);
			$this->db = DB::instance();

			$table = new TableMySQLi('test2', $this->db);
			$table->id('id');
			$table->bool('bool');
			$table->int8('int8');
			$table->int16('int16');
			$table->int24('int24');
			$table->int32('int32');
			$table->int64('int64');
			$table->uint8('uint8');
			$table->uint16('uint16');
			$table->uint24('uint24');
			$table->uint64('uint64');
			$table->float('float');
			$table->float('float2');
			$table->double('double');
			$table->double('double222');
			$table->timestamp('tsupd', true);
			$table->timestamp('ts');
			$table->enum('enum', ['one', 'two', 'three']);
			$table->set('set', ['one', 'two', 'three']);
			$table->string('str10', 10);
			$table->string('str50', 50);
			$table->text('text');

			$table1 = new TableMySQLi('test40', $this->db);
			$table1->id('id');
			$table1->bool('bool');
			$table1->int8('int8');

			$table2 = new TableMySQLi('test50', $this->db);
			$table2->id('id');
			$table2->bool('asd');
			$table2->bool('wewe');

			$this->db->PushTables($table, $table1, $table2);
		}

		public function test() {
			echo 'Catalogs';
		}

		public function test1() {
			echo 'dfdf ';
		}

	}

	Catalogs::init();