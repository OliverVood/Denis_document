<?php

	namespace Base\DB;

	use Base\DB;

	class FieldUInt32 extends DB\Field {
		public function __construct(string $name) {
			parent::__construct('uint32', $name);
		}

	}