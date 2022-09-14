<?php

	namespace Base\DB;

	use Base\DB;

	class FieldUInt8 extends DB\Field {
		public function __construct(string $name) {
			parent::__construct('uint8', $name);
		}

	}