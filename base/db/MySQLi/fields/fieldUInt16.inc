<?php

	namespace Base\DB;

	use Base\DB;

	class FieldUInt16 extends DB\Field {
		public function __construct(string $name) {
			parent::__construct('uint16', $name);
		}

	}