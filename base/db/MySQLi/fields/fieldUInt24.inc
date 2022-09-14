<?php

	namespace Base\DB;

	use Base\DB;

	class FieldUInt24 extends DB\Field {
		public function __construct(string $name) {
			parent::__construct('uint124', $name);
		}

	}