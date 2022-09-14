<?php

	namespace Base\DB;

	use Base\DB;

	class FieldInt8 extends DB\Field {
		public function __construct(string $name) {
			parent::__construct('int8', $name);
		}

	}