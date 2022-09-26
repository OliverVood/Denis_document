<?php

	namespace Base\DB;

	use Base\DB;

	class FieldBoolMySQLi extends DB\FieldMySQLi {
		public function __construct(string $name) {
			parent::__construct('bool', $name);
		}

		public function Check(?array $old) {
			Debug($old);
//			[
//				'type' => '',
//				'unsigned' => true,
//				'null' => true,
//				'primary' => true,
//				'auto_increment' => true,
//				'default' => null,
//				'length' => 20
//			];

			echo "Check field $this->type<br>";
		}

		public function Make() { echo "Make field $this->type<br>"; }

	}